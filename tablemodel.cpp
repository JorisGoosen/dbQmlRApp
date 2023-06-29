#include "tablemodel.h"
#include <QDateTime>
#include "labels.h"

TableModel::TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions)
	: AbstractSizeProviderTable(db), _db(db), _tableName(tableName), _columnDefinitions(columnDefinitions)
{
	_db->tableCreate(_tableName, _columnDefinitions);
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
	if(index.column() < 0 || index.column() >= _columnDefinitions.size())
		return QVariant();

	if(index.row() < 0 || index.row() >= rowCount())
		return QVariant();

	if(role != Qt::DisplayRole)
		return QVariant();

	ColumnDefinition * cd = _columnDefinitions[index.column()];

	QVariant tableVal = _db->tableValue(_tableName, cd, index.row());

	Labels * _labels = Labels::singleton();

	if(cd->columnType() == ColumnType::DateTime)
		return QDateTime::fromSecsSinceEpoch(tableVal.toInt()).toString("yyyy.MM.dd hh:mm");
	else if(cd->columnType() == ColumnType::Label)
	{
		int value = _labels->value(tableVal.toInt());
		return _labels->label(tableVal.toInt()) + (value != -1 ? " " + QString::number(value) : "");
	}
	else if(cd->columnType() == ColumnType::Labels)
	{
		QStringList labelsHuman;
		for(const QString & split : tableVal.toString().split(' '))
			labelsHuman.append(_labels->label(split.toInt()));
		return labelsHuman.join(", ");
	}

	return tableVal;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Vertical)
		return section;

	return section < 0 || section >= _columnDefinitions.size() ? QVariant() : _columnDefinitions[section]->friendlyName();
}

void TableModel::appendRows(const std::vector<QVariantList> & values, const ColumnDefinitions * columnDefinitions)
{
	size_t rowC = rowCount();
	beginInsertRows(QModelIndex(), rowC, rowC + values.size());
	_db->tableWriteRows(_tableName, columnDefinitions ? *columnDefinitions : _columnDefinitions, values);
	endInsertRows();
}

QString TableModel::dbplyrCode() const
{
	QStringList code =
	{
							"library(dplyr);",
							"con <- DBI::dbConnect(RSQLite::SQLite(), dbname = '" + QString::fromStdString(_db->dbFile()) + "');",
							_tableName + "sql <- tbl(con, '"+_tableName+"');",
							"'sql table is called: " + _tableName + "sql'",
							_tableName + " <- " + _tableName + "sql %>% collect()"
	};

	return code.join("\n");
}
