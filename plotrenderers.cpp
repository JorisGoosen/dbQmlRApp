#include "plotrenderers.h"
#include "plotrenderer.h"

#define GENEREERHET(PLOTTYPE, KOLOM, TITEL)										\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::School,		KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Locatie,	KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Sector,		KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Niveau,		KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Leerjaar,	KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Klas,		KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Gender,		KOLOM, TITEL),	\
	new PlotRenderer(this, PLOTTYPE,	PlotFilter::Cultuur,	KOLOM, TITEL)

PlotRenderers::PlotRenderers( QObject *parent)
	: QAbstractListModel{parent}
{
	_plots =
	{
		new PlotRenderer(this,	PlotType::taart,					PlotFilter::Geen, true,	"veiligSchool",		"Veilig op school"				),
		new PlotRenderer(this,	PlotType::taart,					PlotFilter::Geen, true,	"veiligKlas",		"Veilig in de klas"				),
		GENEREERHET(			PlotType::verticaalStaaf,									"veiligSchool",		"Veilig op school"				),
		GENEREERHET(			PlotType::verticaalStaaf,									"veiligKlas",		"Veilig in de klas"				),
		GENEREERHET(			PlotType::horizontaalLabelsGroepen,							"onveiligHier",		"Voel me onveilig in/bij"		),

	};
}

void PlotRenderers::init()
{
	beginResetModel();
	for(PlotRenderer * plot : _plots)
		plot->init();
	endResetModel();
}

int PlotRenderers::rowCount(const QModelIndex &) const
{
	return _plots.size();
}

QVariant PlotRenderers::data(const QModelIndex & index, int role) const
{
	if(index.row() < 0 || index.row() >= int(_plots.size()) || role != Qt::DisplayRole)
		return QVariant();

	return _plots[index.row()]->plotUrl();
}

void PlotRenderers::renderPlots()
{
	for(PlotRenderer * plot : _plots)
		plot->runRCode();
}

void PlotRenderers::plotRenderUpdated(PlotRenderer * plot)
{
	for(size_t i=0; i<_plots.size(); i++)
		if(_plots[i] == plot)
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
