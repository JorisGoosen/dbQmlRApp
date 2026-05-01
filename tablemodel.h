#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QFont>
#include <QFontMetrics>
#include <QHash>
#include <QRect>
#include <QTextOption>

#include "database.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QFont metricFont
               READ metricFont
               WRITE setMetricFont
               NOTIFY metricFontChanged)

    Q_PROPERTY(int cellMargin
               READ cellMargin
               WRITE setCellMargin
               NOTIFY cellMarginChanged)

    Q_PROPERTY(bool upsideDown
               READ upsideDown
               WRITE setUpsideDown
               NOTIFY upsideDownChanged)

    // Optional but useful: allow toggling cache from QML / C++
    Q_PROPERTY(bool cellCacheEnabled
               READ cellCacheEnabled
               WRITE setCellCacheEnabled
               NOTIFY cellCacheEnabledChanged)

public:
    explicit TableModel(Database *db,
                        const QString &tableName,
                        const ColumnDefinitions &columnDefinitions);

    // QAbstractItemModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Explicitly read-only model
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // GUI should not write through this model
    void appendRows(const std::vector<QVariantList> &values,
                    const ColumnDefinitions *columnDefinitions = nullptr);

    const QString &tableName() const { return _tableName; }
    const ColumnDefinitions &columnDefinitions() const { return _columnDefinitions; }

    QString dbplyrCode() const;

    // QML helpers
    Q_INVOKABLE int columnWidthProvider(int col);
    Q_INVOKABLE int rowHeightProvider(int row);

    // Font / layout
    QFont metricFont() const;
    void setMetricFont(const QFont &newMetricFont);

    int cellMargin() const;
    void setCellMargin(int newCellMargin);

    bool upsideDown() const;
    void setUpsideDown(bool newUpsideDown);

    // Explicit refresh hook (call when DB table changes)
    Q_INVOKABLE void refresh();

    // Optional cache control
    bool cellCacheEnabled() const;
    void setCellCacheEnabled(bool enabled);

signals:
    void metricFontChanged();
    void cellMarginChanged();
    void upsideDownChanged();
    void cellCacheEnabledChanged();

private:
    // --- helpers ---
    int cachedRowCount() const;

private:
    // --- immutable config ---
    Database *           _db;
    QString              _tableName;
    ColumnDefinitions    _columnDefinitions;

    // --- cached data ---
    mutable int          _cachedRowCount = -1;

    // --- optional cell cache (for QML redraw storms) ---
    mutable QHash<quint64, QVariant> _cellCache;
    int                   _maxCellCacheEntries = 20000;
    bool                  _cellCacheEnabled = true;

    // --- formatting ---
    QFont                 _metricFont;
    QFontMetrics          _metrics;
    QRect                 _maxBounds;
    QTextOption           _textOption;

    int                   _maxWidthCol = 350;
    int                   _cellMargin = 20;
    bool                  _upsideDown = true;
};

#endif // TABLEMODEL_H
