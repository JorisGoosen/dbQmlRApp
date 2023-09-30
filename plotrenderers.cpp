#include "plotrenderers.h"
#include "plotrenderer.h"
#include <iostream>

#define GENEREERHET(PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::School,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Locatie,	STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Sector,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Niveau,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Jaar,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Klas,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)

#define GENEREERHETDOC(PLOTTYPE, STU, KOLOM, TITEL, W, H)									\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Gender,		STU, KOLOM, TITEL, W, H),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Cultuur,	STU, KOLOM, TITEL, W, H)



PlotRenderers::PlotRenderers( QObject *parent)
	: QAbstractListModel{parent}
{
	_plotFolder = QDir::home();

	const QString naamMap = "SchoolScannerGrafieken";
	if(!_plotFolder.exists(naamMap))
		_plotFolder.mkdir(naamMap);

	_plotFolder = _plotFolder.absoluteFilePath(naamMap);

	_plots =
	{

		//veiligheid leerlingen
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	true,	"veiligSchool",						"Veilig op school",						1280,		1280	)},
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	true,	"veiligKlas",						"Veilig in de klas",					1280,		1280	)},
		{ GENEREERHET(				PlotType::VerticaalStaaf,											true,	"veiligSchool",						"Veilig op school",						1280,		720		)},
		{ GENEREERHET(				PlotType::VerticaalStaaf,											true,	"veiligKlas",						"Veilig in de klas",					1280,		720		)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"onveiligHier",						"Voel me onveilig in bij",				1280,		2560	)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,					PlotFilter::Geen,	true,	"bangOpSchool,graagNaarSchool",		"Hoe graag naar school en hoe bang",	1280,		400		)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"bangOpSchool",						"Bang op school",						1280,		2560	)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"graagNaarSchool",					"Graag naar school",					1280,		2560	)},
		{ GENEREERHET(				PlotType::HoriStaafGroepPerFilter,									true,	"bangOpSchool",						"Bang op school",						1280,		2560	)},

		//veiligheid docenten
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	false,	"veiligSchool",						"Veilig op school",						1280,		1280	)},
		{ new PlotRenderer(this,	PlotType::Taart,								PlotFilter::Geen,	false,	"veiligKlas",						"Veilig in de klas",					1280,		1280	)},
		{ GENEREERHETDOC(			PlotType::VerticaalStaaf,											false,	"veiligSchool",						"Veilig op school",						1280,		720		)},
		{ GENEREERHETDOC(			PlotType::VerticaalStaaf,											false,	"veiligKlas",						"Veilig in de klas",					1280,		720		)},
		//{ GENEREERHETDOC(			PlotType::HoriStaafGroepPerFilter,									false,	"onveiligHier",						"Voel me onveilig in bij",				1280,		2560	)},
		{ new PlotRenderer(this,	PlotType::HoriStaafMeerdereKolommen,					PlotFilter::Geen,	false,	"bangOpSchool,werkMetPlezier",		"Bang op school en werkplezier",		1280,		400		)},
		{ GENEREERHETDOC(			PlotType::HoriStaafGroepPerFilter,									false,	"bangOpSchool",						"Bang op school",						1280,		2560	)},
		{ GENEREERHETDOC(			PlotType::HoriStaafGroepPerFilter,									false,	"werkMetPlezier",					"Werk met plezier",						1280,		2560	)},

		{ new PlotRenderer(this,	PlotType::HoriStaafGroepPerFilter,				PlotFilter::Type,	false,	"bangOpSchool",						"Bang op school",						1280,		1280	)},
	};


}

void PlotRenderers::init()
{
	beginResetModel();
	for(auto & plotL : _plots)
		for(PlotRenderer * plot : plotL)
			plot->init();
	endResetModel();
}


int PlotRenderers::rowCount(const QModelIndex &) const
{
	return _plots.size();
}

QHash<int, QByteArray> PlotRenderers::roleNames() const
{
	static QHash<int, QByteArray> rolNamen = [&](){
		auto namen = QAbstractListModel::roleNames();
		namen[Qt::UserRole+0] = "filters";
		namen[Qt::UserRole+1] = "aspectData";
		namen[Qt::UserRole+2] = "hoogteData";
		namen[Qt::UserRole+3] = "titelData";
		namen[Qt::UserRole+4] = "bestandData";
		namen[Qt::UserRole+5] = "bestandAbsData";
		return namen;
	}();

	return rolNamen;
}

QVariant PlotRenderers::data(const QModelIndex & index, int role) const
{
	if(index.row() < 0 || index.row() >= int(_plots.size()))
		return QVariant();


	QVariantList lijst;
	for(PlotRenderer * plot : _plots[index.row()])
		if(role < Qt::UserRole)
			lijst.append(plot->plotUrl());
		else if(role == Qt::UserRole + 5)
			lijst.append(plot->plotFolder().absoluteFilePath(plot->fileName()));
		else if(role == Qt::UserRole + 4)
			lijst.append(plot->fileName());
		else if(role == Qt::UserRole + 3)
			lijst.append((plot->welkFilter() == PlotFilter::Type ? "Iedereen - " : plot->studenten() ? "Student - " : "Docent - ") + plot->title());
		else if(role == Qt::UserRole + 2)
			lijst.append(plot->height());
		else if(role == Qt::UserRole + 1)
			lijst.append(plot->height() > 0 ? float(plot->height()) / float(plot->width()) : 0);
		else
			lijst.append(PlotFilterToQString(plot->welkFilter()));

	return lijst;
}

void PlotRenderers::renderPlots()
{
	if(!_renderMaar)
		return;

	for(auto & plotL : _plots)
		for(PlotRenderer * plot : plotL)
			plot->runRCodeDelayed();

	setShowMe(true);
}

void PlotRenderers::plotRenderUpdated(PlotRenderer * plot)
{
	for(size_t i=0; i<_plots.size(); i++)
		for(auto * pr : _plots[i])
		if(pr == plot)
		{
			emit dataChanged(index(i), index(i));
			return;
		}
}


void PlotRenderers::setPlotFolder(const QDir & newPlotFolder)
{
	if (_plotFolder == newPlotFolder)
		return;

	_plotFolder = newPlotFolder;
	emit plotFolderChanged();
}

bool PlotRenderers::showMe() const
{
	return _showMe;
}

void PlotRenderers::setShowMe(bool newShowMe)
{
	if (_showMe == newShowMe)
		return;
	_showMe = newShowMe;
	emit showMeChanged();
}

bool PlotRenderers::renderMaar() const
{
	return _renderMaar;
}

void PlotRenderers::setRenderMaar(bool newRenderMaar)
{
	if (_renderMaar == newRenderMaar)
		return;
	_renderMaar = newRenderMaar;
	emit renderMaarChanged();


	renderPlots();
}
