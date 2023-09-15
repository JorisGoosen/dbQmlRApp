#include "tablemodel.h"
#include <QDateTime>
#include "labels.h"

TableModel::TableModel(Database * db, const QString & tableName, const ColumnDefinitions & columnDefinitions)
	: AbstractSizeProviderTable(db), _tableName(tableName), _columnDefinitions(columnDefinitions), _db(db)
{
	_db->tableCreate(_tableName, _columnDefinitions);

	_rowCount = _db->tableRowCount(_tableName);
}

int TableModel::rowCount(const QModelIndex &) const
{
	return _rowCount;
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

	return tableValueVarToString(_db->tableValue(_tableName, cd, index.row()), cd->columnType());
}

QString TableModel::tableValueVarToString(QVariant tableVal, ColumnType type, bool addValue) const
{
	Labels * _labels = Labels::singleton();

	if(type == ColumnType::DateTime)
		return QDateTime::fromSecsSinceEpoch(tableVal.toInt()).toString("yyyy.MM.dd hh:mm");
	else if(type == ColumnType::Label)
	{
		int value = _labels->value(tableVal.toInt());
		return _labels->label(tableVal.toInt()) + (addValue && value != -1 ? " " + QString::number(value) : "");
	}
	else if(type == ColumnType::Labels)
	{
		QStringList labelsHuman;
		for(const QString & split : tableVal.toString().split(' '))
			labelsHuman.append(_labels->label(split.toInt()));
		return labelsHuman.join(", ");
	}

	return tableVal.toString();
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

	_rowCount = _db->tableRowCount(_tableName);
}

void TableModel::clear()
{
	beginResetModel();
	_db->tableDrop(_tableName);
	_db->tableCreate(_tableName, _columnDefinitions);
	endResetModel();

	_rowCount = _db->tableRowCount(_tableName);
}

QStringList TableModel::allLabels(const QString & colName)
{
	ColumnDefinition * cd = nullptr;

	for(ColumnDefinition * cdt : _columnDefinitions)
		if(cdt->dbName() == colName)
		{
			cd = cdt;
			break;
		}

	if(!cd)
		throw std::runtime_error("Unknown column " + colName.toStdString());

	QVariantList	list = _db->tableValues(_tableName, cd);
	QStringList		strs;

	for(QVariant & l : list)
		strs.append(tableValueVarToString(l, cd->columnType()));

	return strs;
}

QStringList TableModel::allUniqueLabels(const QString & colName, bool filter)
{
	ColumnDefinition * cd = nullptr;

	for(ColumnDefinition * cdt : _columnDefinitions)
		if(cdt->dbName() == colName)
		{
			cd = cdt;
			break;
		}

	if(!cd)
		throw std::runtime_error("Unknown column " + colName.toStdString());

	QVariantList	list = _db->tableValues(_tableName, cd);
	QStringList		strs;

	std::map<QString, QVariantList>	filterLists;

	if(filter)
		for(auto & nameLM : _filters)
			if(nameLM.first != colName)
				filterLists[nameLM.first] = _db->tableValues(_tableName, nameLM.second->cd());

	std::set<QString> addedAlready;

	for(size_t r=0; r<list.size(); r++)
	{
		const QVariant & l = list[r];

		QString toText = tableValueVarToString(l, cd->columnType());

		bool filteredOut = false;

		if(filter)
			for(auto & nameList : filterLists)
				if(!_filters[nameList.first]->allowedThroughFilter(tableValueVarToString(nameList.second[r], _filters[nameList.first]->cd()->columnType())))
					filteredOut = true;

		if(!filteredOut && !addedAlready.contains(toText))
		{
			addedAlready.insert(toText);
			strs.append(toText);
		}
	}

	return strs;
}

QString TableModel::dbplyrCode(bool collect) const
{
	QStringList code =
	{
							"library(dplyr);",
							"con <- DBI::dbConnect(RSQLite::SQLite(), dbname = '" + QString::fromStdString(_db->dbFile()) + "');",
							_tableName + "sql <- tbl(con, '"+_tableName+"');",
							"'sql table is called: " + _tableName + "sql'",
	};

	if(collect)
		code.append(_tableName + " <- " + _tableName + "sql %>% collect()");

	return code.join("\n");
}

void TableModel::registerFilter(FilterListModel * lm)
{
	_filters[lm->colName()] = lm;
}
