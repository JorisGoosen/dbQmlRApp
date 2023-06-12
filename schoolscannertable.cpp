#include "schoolscannertable.h"


SchoolScannerTable::SchoolScannerTable(Database * db)
	: TableModel(db, SchoolScannerDefinities::tableName(), SchoolScannerDefinities::columnDefs())
{

}
