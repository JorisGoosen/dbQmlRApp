#include "tablemodel.h"


TableModel::TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions)
	: QAbstractTableModel(db), _db(db), _tableName(tableName), _columnDefinitions(columnDefinitions), _metrics(_metricFont)
{
	//if(!_db->tableExists(_tableName))
	//	_db->tableCreate(_tableName, _columnDefinitions);
}

int TableModel::rowCount(const QModelIndex &) const
{
	return _db->tableRowCount(_tableName);
}

int TableModel::columnCount(const QModelIndex &) const
{
	return _columnDefinitions.size();
}

QVariant TableModel::data(const QModelIndex & index, int role) const
{
	const int rowC = rowCount();
	if(index.column() < 0 || index.column() >= int(_columnDefinitions.size()))
		return QVariant();

	if(index.row() < 0 || index.row() >= rowC)
		return QVariant();

	if(role != Qt::DisplayRole)
		return QVariant();

	QVariant var = _db->tableValue(_tableName, _columnDefinitions[index.column()], _upsideDown ? rowC - (1+index.row()) : index.row());
	
	bool itsAnInt = false;
	int anInt = var.toInt(&itsAnInt);
	

	bool itsADouble = false;
	double dbl = var.toDouble(&itsADouble);
	
	if(anInt && std::abs(double(anInt) - dbl) < 0.000001)
		return QString::number(anInt);
		
	if(itsADouble)
		return QString::number(dbl, 'f', 3);
	
	return var;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Vertical)
		return !_upsideDown ? section : rowCount() - (1+section);

	return section < 0 || section >= int(_columnDefinitions.size()) ? QVariant() : _columnDefinitions[section]->friendlyName();
}

void TableModel::appendRows(const std::vector<QVariantList> & values, const ColumnDefinitions * columnDefinitions)
{
	assert(false);
	size_t rowC = rowCount();
	if(_upsideDown)		beginResetModel();
	else				beginInsertRows(QModelIndex(), rowC, rowC + values.size());
	
	_db->tableWriteRows(_tableName, columnDefinitions ? *columnDefinitions : _columnDefinitions, values);
	
	if(_upsideDown)		endResetModel();
	else				endInsertRows();
}

QString TableModel::dbplyrCode() const
{
	QStringList code;

	code.append({
							_tableName + "sql <- tbl(con, '"+_tableName+"');",
							"'sql table is called: " + _tableName + "sql'" /*,
							_tableName + " <- " + _tableName + "sql %>% collect()"*/
	});

	return code.join("\n");
}

int TableModel::columnWidthProvider(int col)
{
	QString header = headerData(col, Qt::Horizontal).toString();

	QRect bounds = _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.width();

	for(int row=0; row<rowCount() && row < 10; row++)
		largestVal = std::max(largestVal, _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, data(index(row, col)).toString()).width());

	return std::min(largestVal, _maxBounds.width()) + _cellMargin;
}

int TableModel::rowHeightProvider(int row)
{

	QString header = headerData(row, Qt::Vertical).toString();

	QRect bounds = _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, header);

	int largestVal = bounds.height();

	for(int column=0; column<columnCount(); column++)
	{
		const QString & val = data(index(row, column)).toString();
		largestVal = std::max(largestVal, _metrics.boundingRect(_maxBounds, Qt::TextWordWrap, val).height());
	}

	return largestVal + _cellMargin;
}

QFont TableModel::metricFont() const
{
	return _metricFont;
}

void TableModel::setMetricFont(const QFont & newMetricFont)
{
	if (_metricFont == newMetricFont)
	{

		_metricFont = newMetricFont;
		emit metricFontChanged();
	}

	_metrics = QFontMetrics(_metricFont);

	_textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	_maxBounds = _metrics.boundingRect(QString(_maxWidthCol, 'X'), _textOption);
}

int TableModel::cellMargin() const
{
	return _cellMargin;
}

void TableModel::setCellMargin(int newCellMargin)
{
	if (_cellMargin == newCellMargin)
		return;
	_cellMargin = newCellMargin;
	emit cellMarginChanged();
}

bool TableModel::upsideDown() const
{
	return _upsideDown;
}

void TableModel::setUpsideDown(bool newUpsideDown)
{
	if (_upsideDown == newUpsideDown)
		return;
	beginResetModel();
	_upsideDown = newUpsideDown;
	emit upsideDownChanged();
	endResetModel();
}
