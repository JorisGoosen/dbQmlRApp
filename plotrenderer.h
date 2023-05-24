#ifndef PLOTRENDERER_H
#define PLOTRENDERER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTimer>

class PlotRenderer : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString	rCode		READ rCode		WRITE setRCode		NOTIFY rCodeChanged		)
	Q_PROPERTY(int		width		READ width		WRITE setWidth		NOTIFY widthChanged		)
	Q_PROPERTY(int		height		READ height		WRITE setHeight		NOTIFY heightChanged	)
	Q_PROPERTY(int		revision	READ revision						NOTIFY revisionChanged	)
	Q_PROPERTY(QDir		plotFolder	READ plotFolder	WRITE setPlotFolder	NOTIFY plotFolderChanged)
	Q_PROPERTY(QString	fileName	READ fileName	WRITE setFileName	NOTIFY fileNameChanged	)
	Q_PROPERTY(QString	plotUrl		READ plotUrl						NOTIFY plotUrlChanged)

public:
	explicit				PlotRenderer(QFile		rFile, QString fileName="plot.png", QDir outputFolder = QDir(), QObject *parent = nullptr);
	explicit				PlotRenderer(QString	rCode, QString fileName="plot.png", QDir outputFolder = QDir(), QObject *parent = nullptr);

				QString		rCode()			const { return _rCode;			}
				int			width()			const { return _width;			}
				int			height()		const { return _height;			}
				int			revision()		const { return _revision;		}
				QDir		plotFolder()	const { return _plotFolder;		}
				QString		plotUrl()		const;
				QString		fileName()		const { return _fileName;		}


				void		setRCode(const QString & newRCode);
				void		setWidth(int newWidth);
				void		setHeight(int newHeight);
				void		setPlotFolder(const QDir & newPlotFolder);
				void		setFileName(const QString & newFileName);
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

private:
				void		init();

private:
				QString		_rCode,
							_fileName;
				int			_width		= 0,
							_height		= 0,
							_revision	= 0;
				QDir		_plotFolder;
				QTimer		_timer;
				bool		_running	= false;
};

#endif // PLOTRENDERER_H
