#include "tablemodel.h"

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

	return _db->tableValue(_tableName, _columnDefinitions[index.column()], index.row());
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
