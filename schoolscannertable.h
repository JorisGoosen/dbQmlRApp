#ifndef SCHOOLSCANNERTABLE_H
#define SCHOOLSCANNERTABLE_H

#include "tablemodel.h"
#include "schoolscannerdefinities.h"

class SchoolScannerTable : public TableModel
{
public:
	SchoolScannerTable(Database * db);

	const ColumnDefinition * findDbColumn(const QString & csvName);

private:


};

#endif // SCHOOLSCANNERTABLE_H
