#ifndef PLOTRENDERER_H
#define PLOTRENDERER_H

#include "enumutilities.h"
#include <QObject>
#include <QFile>
#include <QDir>
#include <QTimer>

DECLARE_ENUM(PlotType,		horizontaalPerLabel, horizontaalMeerdere, horizontaalLabelsGroepen, horizontaalLabelPerTypeRespondent, verticaalStaaf, taart)
DECLARE_ENUM(PlotFilter,	Geen, School, Locatie, Sector, Niveau, Leerjaar, Klas, Gender, Cultuur)

class PlotRenderers;

class PlotRenderer : public QObject
{
	friend PlotRenderers;

	Q_OBJECT
	Q_PROPERTY(QString		rCode		READ rCode		WRITE setRCode		NOTIFY rCodeChanged		)
	Q_PROPERTY(int			width		READ width		WRITE setWidth		NOTIFY widthChanged		)
	Q_PROPERTY(int			height		READ height		WRITE setHeight		NOTIFY heightChanged	)
	Q_PROPERTY(int			revision	READ revision						NOTIFY revisionChanged	)
	Q_PROPERTY(QString		fileName	READ fileName						NOTIFY fileNameChanged	)
	Q_PROPERTY(QString		plotUrl		READ plotUrl						NOTIFY plotUrlChanged	)
	Q_PROPERTY(PlotType		welkPlot	READ welkPlot	WRITE setWelkPlot	NOTIFY welkPlotChanged	)
	Q_PROPERTY(PlotFilter	welkFilter	READ welkFilter WRITE setWelkFilter NOTIFY welkFilterChanged)
	Q_PROPERTY(QString		kolom		READ kolom		WRITE setKolom		NOTIFY kolomChanged		)
	Q_PROPERTY(QString		title		READ title		WRITE setTitle		NOTIFY titleChanged		)


public:
	explicit				PlotRenderer(PlotRenderers * renderers, PlotType plotType, PlotFilter filter, bool studenten = true, const QString & kolom = "", const QString & titel = "", int width = 1024, int height = 1024);
	/*explicit				PlotRenderer(QFile		rFile, QString fileName="plot.png", QDir outputFolder = QDir(), QObject *parent = nullptr);
	explicit				PlotRenderer(QString	rCode, QString fileName="plot.png", QDir outputFolder = QDir(), QObject *parent = nullptr);*/

				QString		rCode()			const { return _rCode;			}
				int			width()			const { return _width;			}
				int			height()		const { return _height;			}
				int			revision()		const { return _revision;		}
				QDir		plotFolder()	const;
				QString		plotUrl()		const;
				QString		fileName()		const { return _fileName;		}
				PlotType	welkPlot()		const;
				QString		title()			const;
				PlotFilter	welkFilter()	const;
				QString		kolom()			const;


				void		setWidth(		int					  newWidth		);
				void		setHeight(		int					  newHeight		);
				void		setRCode(		const QString		& newRCode		);
				void		setKolom(		const QString		& newKolom		);
				void		setWelkPlot(	const PlotType		& newWelkPlot	);
				void		setTitle(		const QString		& newTitle		);
				void		setWelkFilter(	const PlotFilter	& newWelkFilter	);

				void		incRevision();

public slots:
				void		runRCode();
				void		runRCodeDelayed();

signals:
				void		rCodeChanged();
				void		runRCommand(QString rCode);
				void		widthChanged();
				void		heightChanged();
				void		revisionChanged();
				void		plotFolderChanged();
				void		fileNameChanged();
				void		plotUrlChanged();
				void		welkPlotChanged();
				void		titleChanged();
				void		welkFilterChanged();
				void		kolomChanged();
				void		iUpdated(PlotRenderer * me);

private:
				void		init();

				PlotRenderers	*	_ouder	= nullptr;
				QString				_rCode,
									_fileName,
									_title,
									_kolom;
				bool				_studenten;
				int					_width,
									_height,
									_revision	= 0;
				QTimer				_timer;
				PlotType			_welkPlot	= PlotType::horizontaalLabelPerTypeRespondent;
				PlotFilter			_welkFilter = PlotFilter::Geen;
};

#endif // PLOTRENDERER_H
