#define ENUM_DECLARATION_CPP
#include "columndefinition.h"
#include <QDateTime>

QString ColumnDefinition::friendlyName() const
{
	return _friendlyName;
}

void ColumnDefinition::setFriendlyName(const QString & newFriendlyName)
{
	if (_friendlyName == newFriendlyName)
		return;

	_friendlyName = newFriendlyName;
	emit friendlyNameChanged();
}

QString ColumnDefinition::dbName() const
{
	return _dbName;
}

void ColumnDefinition::setDbName(const QString & newDbName)
{
	if (_dbName == newDbName)
		return;

	_dbName = newDbName;
	emit dbNameChanged();
}

ColumnType ColumnDefinition::columnType() const
{
	return _columnType;
}

QString ColumnDefinition::dbColType() const
{
	switch(_columnType)
	{
	case ColumnType::PrimaryKey:
		return "INTEGER PRIMARY KEY";

	case ColumnType::NumInt:
	case ColumnType::NumBool:
	case ColumnType::DateTime:
	case ColumnType::Label:
		return "INT";

	case ColumnType::Duration:
	case ColumnType::NumDbl:
		return "REAL";

	case ColumnType::Text:
		return "TEXT";
	}
}

QString ColumnDefinition::convertQVariantToDbValue(QVariant val) const
{
	switch(_columnType)
	{
	case ColumnType::NumInt:
	case ColumnType::PrimaryKey:
		return QString::number(val.toInt());

	case ColumnType::NumBool:
		return val.toInt() == 0 ? "False" : "True";

	case ColumnType::NumDbl:
	case ColumnType::Duration: //seconds?
		return QString::number(val.toDouble());

	case ColumnType::DateTime:
		return QString::number(val.toDateTime().toSecsSinceEpoch());

	case ColumnType::Text:
		return val.toString();

	case ColumnType::Label:
		//Depending on the query we might get an actual int-value, representing either ID or order, or we might get the actual labelstring...
		switch(val.typeId())
		{
		case QMetaType::Int:
			return QString::number(val.toInt());

		default:
		case QMetaType::QString:
			return val.toString();
		}

	}
}

void ColumnDefinition::setColumnType(const ColumnType & newColumnType)
{
	if (_columnType == newColumnType)
		return;

	_columnType = newColumnType;
	emit columnTypeChanged();
}

