#ifndef CUSTOMCSVDBTABLE_H
#define CUSTOMCSVDBTABLE_H

#include "tablemodel.h"

class CustomCsvDbTable : public TableModel
{
	Q_OBJECT
public:
	CustomCsvDbTable(Database * db);

	void loadIntoDefinities();

private:
	static ColumnDefinitions _colDefs;
};

#endif // CUSTOMCSVDBTABLE_H
