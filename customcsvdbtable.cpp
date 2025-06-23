#include "customcsvdbtable.h"
#include "schoolscannerdefinities.h"

ColumnDefinitions CustomCsvDbTable::_colDefs = {
	new ColumnDefinition("Csv Naam",		"csvName",		ColumnType::Text),
	new ColumnDefinition("DB Naam",			"dbName",		ColumnType::Text),
	new ColumnDefinition("Type resp",		"type",			ColumnType::Text) };

CustomCsvDbTable::CustomCsvDbTable(Database * db)
	: TableModel(db, "customCsvToDb", _colDefs)
{}

void CustomCsvDbTable::loadIntoDefinities()
{
	int columnCsv = columnIndex("csvName"),
		columnDb  = columnIndex("dbName"),
		columnDoc = columnIndex("type");

	for(int i=0; i<rowCount(); i++)
	{
		QString csv = data(index(i, columnCsv)).toString(),
				db  = data(index(i, columnDb )).toString(),
				doc = data(index(i, columnDoc)).toString();

		SchoolScannerDefinities::addCsvToMaps(csv, db, doc == "Docenten");
	}
}
