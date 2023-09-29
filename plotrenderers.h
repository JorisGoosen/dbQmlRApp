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
	Q_PROPERTY(bool			showMe		READ showMe		WRITE setShowMe		NOTIFY showMeChanged)
	Q_PROPERTY(bool			renderMaar	READ renderMaar WRITE setRenderMaar NOTIFY renderMaarChanged)

public:
	explicit	PlotRenderers(QObject *parent = nullptr);
	void		init();

	QHash<int, QByteArray>
				roleNames() const override;
	int			rowCount(	const QModelIndex & parent = QModelIndex())				const override;
	QVariant	data(		const QModelIndex &index, int role = Qt::DisplayRole)	const override;


	QDir		plotFolder()	const { return _plotFolder;		}
	bool		showMe() const;
	bool		renderMaar() const;

	void		setPlotFolder(	const QDir			& newPlotFolder);
	void		setShowMe(bool newShowMe);
	void		setRenderMaar(bool newRenderMaar);



signals:
	QString		runRCommand(QString rCode);
	void		initRCodeChanged();
	void		plotFolderChanged();
	void		showMeChanged();
	void		renderMaarChanged();

public slots:
	void		renderPlots();
	void		plotRenderUpdated(PlotRenderer * plot);

private:
	std::vector<std::vector<PlotRenderer*>>	_plots;
	QDir									_plotFolder;
	bool									_showMe		= false,
											_renderMaar = false;
};

#endif // PLOTRENDERERS_H
