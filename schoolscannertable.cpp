#include "schoolscannertable.h"


SchoolScannerTable::SchoolScannerTable(Database * db)
	: TableModel(db, SchoolScannerDefinities::tableName(), SchoolScannerDefinities::columnDefs())
{
	_textOnly = new TableModel(db, SchoolScannerDefinities::tableName() + "TextOnly", SchoolScannerDefinities::columnDefsText());

	_filters = {
		&_school,
		&_locatie,
		&_sector,
		&_niveau,
		&_leerjaar,
		&_klas,
		&_gender,
		&_cultuur
	};

	connect(this, &QAbstractTableModel::modelReset, this, &SchoolScannerTable::loadFilters);

	loadFilters();
}

const ColumnDefinition * SchoolScannerTable::findDbColumn(const QString & csvName)
{
	for(const auto * cd : SchoolScannerDefinities::columnDefs())
		if(cd->csvColumnIsForMe(csvName))
			return cd;
	return nullptr;
}

QString SchoolScannerTable::dbplyerFilter() const
{
	//to be put in something like: filter(starwars, hair_color == "none" & eye_color == "black")
	QStringList filters;

	for(FilterListModel * flm : _filters)
	{
		QString code = flm->dbplyerFilter();

		if(!code.isEmpty())
			filters.push_back(code);
	}

	return filters.join("&");
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

	_textOnly->clear();
	std::vector<QStringList>	columns;

	std::vector<QVariantList> textOnlyValues;

	for(ColumnDefinition * cd : _columnDefinitions)
		columns.push_back(allLabels(cd->dbName()));

	int rowC = rowCount();
	for(int row=0; row<rowC; row++)
	{
		QVariantList rowVals;

		for(int col=0; col<columns.size(); col++)
			rowVals.push_back(columns[col][row]);

		textOnlyValues.push_back(rowVals);
	}

	_textOnly->appendRows(textOnlyValues);
}

void SchoolScannerTable::initPlots()
{
	PlotRenderer			*	piePlot = nullptr;

	QFile	rWriteImage(":/R/writeImage.R"	);

	rWriteImage.open(	QIODeviceBase::ReadOnly);

	emit runRCommand(rWriteImage.readAll());
	emit runRCommand(_textOnly->dbplyrCode());
	QString dbFilter = dbplyerFilter();

	if(dbFilter != "")
		emit runRCommand("filter(" + _textOnly->tableName() + ", " + dbFilter + ");");

	piePlot = new PlotRenderer(QFile(":/R/pie.R"),	"pie.png");

	QObject::connect(this, &SchoolScannerTable::plotWidthChanged,	piePlot,	&PlotRenderer::setWidth);
	QObject::connect(this, &SchoolScannerTable::plotHeightChanged,	piePlot,	&PlotRenderer::setHeight);

	QObject::connect(piePlot,		&PlotRenderer::runRCommand,		this,	&SchoolScannerTable::runRCommand);

	emit addContextProperty("plotPie",	piePlot);
}
