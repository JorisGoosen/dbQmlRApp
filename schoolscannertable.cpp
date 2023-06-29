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

	for(FilterListModel * lm : _filters)
	{
		for(ColumnDefinition * cd : SchoolScannerDefinities::columnDefsText())
			if(lm->colName() == cd->dbName())
				lm->setCd(cd);

		_textOnly->registerFilter(lm);
	}

	connect(this,		&QAbstractTableModel::modelReset,	this, &SchoolScannerTable::loadFilters);

	connect(&_school,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_locatie,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_sector,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_niveau,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_leerjaar, &FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_klas,		&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_gender,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);
	connect(&_cultuur,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::initRStuff,	Qt::QueuedConnection);

	connect(&_school,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_locatie,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_sector,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_niveau,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_leerjaar, &FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_klas,		&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_gender,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);
	connect(&_cultuur,	&FilterListModel::filterChanged,	this, &SchoolScannerTable::loadFilters);

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

	_school		.setLabels(_textOnly->allUniqueLabels("school"));
	_locatie	.setLabels(_textOnly->allUniqueLabels("locatie"));
	_sector		.setLabels(_textOnly->allUniqueLabels("sector"));
	_niveau		.setLabels(_textOnly->allUniqueLabels("niveau"));
	_leerjaar	.setLabels(_textOnly->allUniqueLabels("jaar"));
	_klas		.setLabels(_textOnly->allUniqueLabels("klas"));
	_gender		.setLabels(_textOnly->allUniqueLabels("gender"));
	_cultuur	.setLabels(_textOnly->allUniqueLabels("cultuur"));

	emit schoolChanged();
	emit locatieChanged();
	emit sectorChanged();
	emit niveauChanged();
	emit leerjaarChanged();
	emit klasChanged();
	emit genderChanged();
	emit cultuurChanged();
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
