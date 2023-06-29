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

	connect(this,		&QAbstractTableModel::modelReset,	this, &SchoolScannerTable::loadFilters);
	connect(&_school,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_locatie,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_sector,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_niveau,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_leerjaar, &FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_klas,		&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_gender,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);
	connect(&_cultuur,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff);

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

	std::vector<QStringList>	columns;

	std::vector<QVariantList> textOnlyValues;

	for(ColumnDefinition * cd : _columnDefinitions)
		columns.push_back(allLabels(cd->dbName()));

	int rowC = rowCount();
	for(int row=_textOnly->rowCount(); row<rowC; row++)
	{
		QVariantList rowVals;

		for(int col=0; col<columns.size(); col++)
			rowVals.push_back(columns[col][row]);

		textOnlyValues.push_back(rowVals);
	}

	_textOnly->appendRows(textOnlyValues);
}

void SchoolScannerTable::initRStuff()
{

	QFile	rWriteImage(":/R/writeImage.R"	);

	rWriteImage.open(	QIODeviceBase::ReadOnly);

	emit runRCommand(rWriteImage.readAll());
	emit runRCommand(_textOnly->dbplyrCode(false));
	QString dbFilter = dbplyerFilter();

	if(dbFilter != "")
		emit runRCommand(_textOnly->tableName() + "sql <- filter(" + _textOnly->tableName() + "sql, " + dbFilter + ");");

	emit runRCommand(_textOnly->tableName() + " <- " + _textOnly->tableName() + "sql %>% collect()");

	if(_plotPie)
		_plotPie->runRCode();
}

void SchoolScannerTable::initPlots()
{
	initRStuff();

	_plotPie = new PlotRenderer(QFile(":/R/pie.R"),	"pie.png");

	QObject::connect(this, &SchoolScannerTable::plotWidthChanged,	_plotPie,	&PlotRenderer::setWidth);
	QObject::connect(this, &SchoolScannerTable::plotHeightChanged,	_plotPie,	&PlotRenderer::setHeight);

	QObject::connect(_plotPie,		&PlotRenderer::runRCommand,		this,	&SchoolScannerTable::runRCommand);

	emit addContextProperty("plotPie",	_plotPie);
}
