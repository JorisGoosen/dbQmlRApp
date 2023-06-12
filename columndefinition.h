#ifndef COLUMNDEFINITION_H
#define COLUMNDEFINITION_H

#include <QObject>
#include "enumutilities.h"
#include <QVariant>

DECLARE_ENUM(ColumnType, NumDbl, NumInt, NumBool, DateTime, Duration, Text, Label, PrimaryKey)

class ColumnDefinition : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString		dbName			READ dbName			WRITE setDbName			NOTIFY dbNameChanged		)
	Q_PROPERTY(ColumnType	columnType		READ columnType		WRITE setColumnType		NOTIFY columnTypeChanged	)
	Q_PROPERTY(QString		friendlyName	READ friendlyName	WRITE setFriendlyName	NOTIFY friendlyNameChanged	)

public:
	ColumnDefinition(const QString & friendlyName, const QString & dbName, ColumnType columnType)
		: _friendlyName(friendlyName), _dbName(dbName), _columnType(columnType) {}


	QString		friendlyName()	const;
	QString		dbName()		const;
	ColumnType	columnType()	const;
	QString		dbColType()		const;

	QString		convertQVariantToDbValue(QVariant val) const;

	void setFriendlyName(	const QString & newFriendlyName);
	void setDbName(			const QString & newDbName);
	void setColumnType(		const ColumnType & newColumnType);



signals:
	void friendlyNameChanged();
	void dbNameChanged();
	void columnTypeChanged();

private:
	QString		_friendlyName,
				_dbName;
	ColumnType	_columnType;
};

typedef std::vector<ColumnDefinition*> ColumnDefinitions;

#endif // COLUMNDEFINITION_H
