#ifndef PLOTRENDERERS_H
#define PLOTRENDERERS_H

#include <QAbstractListModel>
#include <vector>
#include <QDir>

class PlotRenderer;

class PlotRenderers : public QAbstractListModel
{
	Q_OBJECT
	Q_PROPERTY(QDir			plotFolder	READ plotFolder	WRITE setPlotFolder	NOTIFY plotFolderChanged)

public:
	explicit	PlotRenderers(QObject *parent = nullptr);
	void		init();

	int			rowCount(	const QModelIndex & parent = QModelIndex())				const override;
	QVariant	data(		const QModelIndex &index, int role = Qt::DisplayRole)	const override;

	QDir		plotFolder()	const { return _plotFolder;		}
	void		setPlotFolder(	const QDir			& newPlotFolder);

signals:
	void		runRCommand(QString rCode);
	void		initRCodeChanged();
	void		plotFolderChanged();

public slots:
	void		renderPlots();
	void		plotRenderUpdated(PlotRenderer * plot);

private:
	std::vector<PlotRenderer*>	_plots;
	QDir						_plotFolder;
};

#endif // PLOTRENDERERS_H
