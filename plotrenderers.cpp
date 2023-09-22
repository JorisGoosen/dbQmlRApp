#include "plotrenderers.h"
#include "plotrenderer.h"

PlotRenderers::PlotRenderers( QObject *parent)
	: QAbstractListModel{parent}
{
	_plots =
	{
		new PlotRenderer(this, PlotType::taart, PlotFilter::Studenten, "veiligSchool"),
		new PlotRenderer(this, PlotType::taart, PlotFilter::Studenten, "veiligKlas")
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
