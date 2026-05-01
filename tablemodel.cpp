#include "tablemodel.h"

#include <QDebug>
#include <QFontMetrics>
#include <QHash>
#include <QRect>
#include <QTextOption>
#include <QtGlobal>
#include <cmath>
#include <algorithm>

// ---- helpers ----
static inline quint64 makeCellKey(int row, int col)
{
    return (quint64(quint32(row)) << 32) | quint64(quint32(col));
}

TableModel::TableModel(Database *db,
                       const QString &tableName,
                       const ColumnDefinitions &columnDefinitions)
    : QAbstractTableModel(db),
      _db(db),
      _tableName(tableName),
      _columnDefinitions(columnDefinitions),
      _metrics(_metricFont)
{
    // Read-only model: do NOT create tables from GUI.
    // If you need table creation, do it elsewhere (writer / setup phase).

    // Cache defaults
    _cachedRowCount = -1;

    // Cell cache: helpful for QML which calls data() a lot during painting.
    _maxCellCacheEntries = 20000;  // adjust if needed
    _cellCache.reserve(_maxCellCacheEntries);

    _textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    _maxBounds = _metrics.boundingRect(QString(_maxWidthCol, 'X'), _textOption);
}

// -----------------
// Core: row/col counts
// -----------------

int TableModel::rowCount(const QModelIndex &) const
{
    // Never do transaction begin/end in paint-path functions.
    // Make this cheap and non-reentrant by caching.
    return cachedRowCount();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return int(_columnDefinitions.size());
}

// -----------------
// Read-only flags (prevents implicit edit paths in QML)
// -----------------

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    // Explicitly read-only.
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

// -----------------
// Data access
// -----------------

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    const int col = index.column();
    if (col < 0 || col >= int(_columnDefinitions.size()))
    {
        return QVariant();
    }

    const int rowC = cachedRowCount();
    const int row = index.row();
    if (row < 0 || row >= rowC)
    {
        return QVariant();
    }

    // Compute actual row (upsideDown support) without calling rowCount() again.
    const int actualRow = _upsideDown ? (rowC - 1 - row) : row;

    // Optional: cache display values to reduce DB load during redraw.
    const quint64 key = makeCellKey(actualRow, col);
    if (_cellCacheEnabled)
    {
        const auto it = _cellCache.constFind(key);
        if (it != _cellCache.constEnd())
        {
            return it.value();
        }
    }

    // NOTE: Do not wrap this in transactions here.
    // The Database layer should hold a stable read-only connection (SQLITE_OPEN_READONLY).
    QVariant raw = _db->tableValue(_tableName, _columnDefinitions[col], actualRow);

    // Format values consistently (fixes an old bug: 0 was never treated as int).
    bool okInt = false;
    const int asInt = raw.toInt(&okInt);

    bool okDbl = false;
    const double asDbl = raw.toDouble(&okDbl);

    QVariant display;
    if (okInt && okDbl && std::abs(double(asInt) - asDbl) < 0.000001)
    {
        display = QString::number(asInt);
    }
    else if (okDbl)
    {
        display = QString::number(asDbl, 'f', 3);
    }
    else
    {
        display = raw;
    }

    if (_cellCacheEnabled)
    {
        // Simple eviction strategy (keep it simple and predictable):
        // If the cache grows too large, clear it.
        if (_cellCache.size() >= _maxCellCacheEntries)
        {
            _cellCache.clear();
        }
        _cellCache.insert(key, display);
    }

    return display;
}

// -----------------
// Headers
// -----------------

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Vertical)
    {
        const int rowC = cachedRowCount();
        if (section < 0 || section >= rowC)
        {
            return QVariant();
        }
        return !_upsideDown ? section : (rowC - 1 - section);
    }

    if (section < 0 || section >= int(_columnDefinitions.size()))
    {
        return QVariant();
    }

    return _columnDefinitions[section]->friendlyName();
}

// -----------------
// Writes (disabled for GUI read-only safety)
// -----------------

void TableModel::appendRows(const std::vector<QVariantList> & /*values*/,
                            const ColumnDefinitions * /*columnDefinitions*/)
{
    // This model is designed to be read-only in the QML GUI context.
    // If some part of the app calls appendRows(), that is a design error.
    qWarning() << "TableModel::appendRows() called, but TableModel is read-only. Ignoring.";
}

// -----------------
// Convenience: dbplyr code
// -----------------

QString TableModel::dbplyrCode() const
{
    QStringList code;

    code.append({
        _tableName + "sql <- tbl(con, '" + _tableName + "');",
        "'sql table is called: " + _tableName + "sql'"
    });

    return code.join("\n");
}

// -----------------
// Column/row size providers
// -----------------

int TableModel::columnWidthProvider(int col)
{
    const QString header = headerData(col, Qt::Horizontal).toString();
    QRect bounds = _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, header);
    int largestVal = bounds.width();

    // Use cached rowCount to avoid repeated DB hits.
    const int rc = cachedRowCount();
    const int sampleRows = std::min(rc, 10);

    for (int row = 0; row < sampleRows; row++)
    {
        const QString v = data(index(row, col), Qt::DisplayRole).toString();
        largestVal = std::max(largestVal, _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, v).width());
    }

    return std::min(largestVal, _maxBounds.width()) + _cellMargin;
}

int TableModel::rowHeightProvider(int row)
{
    const QString header = headerData(row, Qt::Vertical).toString();
    QRect bounds = _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, header);
    int largestVal = bounds.height();

    for (int column = 0; column < columnCount(); column++)
    {
        const QString v = data(index(row, column), Qt::DisplayRole).toString();
        largestVal = std::max(largestVal, _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, v).height());
    }

    return largestVal + _cellMargin;
}

// -----------------
// Font / metrics
// -----------------

QFont TableModel::metricFont() const
{
    return _metricFont;
}

void TableModel::setMetricFont(const QFont &newMetricFont)
{
    if (_metricFont == newMetricFont)
    {
        return;
    }

    _metricFont = newMetricFont;
    _metrics = QFontMetrics(_metricFont);

    _textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    _maxBounds = _metrics.boundingRect(QString(_maxWidthCol, 'X'), _textOption);

    emit metricFontChanged();
}

// -----------------
// Margins
// -----------------

int TableModel::cellMargin() const
{
    return _cellMargin;
}

void TableModel::setCellMargin(int newCellMargin)
{
    if (_cellMargin == newCellMargin)
    {
        return;
    }

    _cellMargin = newCellMargin;
    emit cellMarginChanged();
}

// -----------------
// Upside-down ordering
// -----------------

bool TableModel::upsideDown() const
{
    return _upsideDown;
}

void TableModel::setUpsideDown(bool newUpsideDown)
{
    if (_upsideDown == newUpsideDown)
    {
        return;
    }

    beginResetModel();
    _upsideDown = newUpsideDown;

    // Cache depends on row mapping, clear it.
    _cellCache.clear();

    emit upsideDownChanged();
    endResetModel();
}

// -----------------
// Explicit refresh hooks (call this when DB table changes)
// -----------------

void TableModel::refresh()
{
    beginResetModel();

    _cachedRowCount = -1;
    _cellCache.clear();

    endResetModel();
}

int TableModel::cachedRowCount() const
{
    if (_cachedRowCount >= 0)
    {
        return _cachedRowCount;
    }

    // Single DB hit; no transactions here.
    _cachedRowCount = _db->tableRowCount(_tableName);
    return _cachedRowCount;
}

bool TableModel::cellCacheEnabled() const
{
    return _cellCacheEnabled;
}

void TableModel::setCellCacheEnabled(bool enabled)
{
    if (_cellCacheEnabled == enabled)
    {
        return;
    }

    _cellCacheEnabled = enabled;
    if (!_cellCacheEnabled)
    {
        _cellCache.clear();
    }
    emit cellCacheEnabledChanged();
}
