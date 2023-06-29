#ifndef SCHOOLSCANNERDEFINITIES_H
#define SCHOOLSCANNERDEFINITIES_H

#include "columndefinition.h"

class SchoolScannerDefinities
{
public:
	static const ColumnDefinitions				& columnDefs()		{ return _columnDefs;		}
	static const QString						& tableName()		{ return _tableName;		}
	static const std::map<QString, QString>		& mapCsvToDb()		{ return _mapCsvToDb;		}
	static const ColumnDefinitions				& columnDefsText();

private:
	SchoolScannerDefinities() {}

	static const ColumnDefinitions				_columnDefs;
	static ColumnDefinitions				*	_columnDefsText;
	static const QString						_tableName;
	static const std::map<QString, QString>		_mapCsvToDb;
};

#endif // SCHOOLSCANNERDEFINITIES_H