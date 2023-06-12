#ifndef SCHOOLSCANNERDEFINITIES_H
#define SCHOOLSCANNERDEFINITIES_H

#include "columndefinition.h"

class SchoolScannerDefinities
{
public:
	static const ColumnDefinitions	& columnDefs();
	static const QString			& tableName() { return _tableName; };

private:
	SchoolScannerDefinities() {}

	static const ColumnDefinitions	_columnDefs;
	static const QString			_tableName;
};

#endif // SCHOOLSCANNERDEFINITIES_H
