#include "schoolscannertable.h"


SchoolScannerTable::SchoolScannerTable(Database * db)
	: TableModel(db, SchoolScannerDefinities::tableName(), SchoolScannerDefinities::columnDefs())
{
	connect(this, &QAbstractTableModel::modelReset, this, &SchoolScannerTable::loadFilters);
}

const ColumnDefinition * SchoolScannerTable::findDbColumn(const QString & csvName)
{
	for(const auto * cd : SchoolScannerDefinities::columnDefs())
		if(cd->csvColumnIsForMe(csvName))
			return cd;
	return nullptr;
}

void SchoolScannerTable::loadFilters()
{
	_school		.setLabels(allUniqueLabels("school"));
	_locatie	.setLabels(allUniqueLabels("locatie"));
	_sector		.setLabels(allUniqueLabels("sector"));
	_niveau		.setLabels(allUniqueLabels("niveau"));
	_leerjaar	.setLabels(allUniqueLabels("jaar"));
	_klas		.setLabels(allUniqueLabels("klas"));
	_gender		.setLabels(allUniqueLabels("gender"));
	_cultuur	.setLabels(allUniqueLabels("cultuur"));

	emit schoolChanged();
	emit locatieChanged();
	emit sectorChanged();
	emit niveauChanged();
	emit leerjaarChanged();
	emit klasChanged();
	emit genderChanged();
	emit cultuurChanged();
}
