#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QUrl>
#include <QObject>
#include <QSettings>
#include "labels.h"

class Database;


class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList	qmlsShown		READ qmlsShown										NOTIFY qmlsShownChanged			)
	Q_PROPERTY(QString		dbPath			READ dbPath				WRITE setDbPath				NOTIFY dbPathChanged			)
	Q_PROPERTY(QString		dbPathKort		READ dbPathKort										NOTIFY dbPathChanged			)
	Q_PROPERTY(QString		settingsCode	READ settingsCode		WRITE setSettingsCode		NOTIFY settingsChanged			)
	Q_PROPERTY(QUrl			envPicSource	READ envPicSource		WRITE setEnvPicSource		NOTIFY envPicSourceChanged		)
	Q_PROPERTY(QString		envPicError		READ envPicError		WRITE setEnvPicError		NOTIFY envPicErrorChanged		)
	

public:
	explicit	MainModel(Database * db, QObject *parent = nullptr);

	QStringList qmlsShown()			const;
	QString		dbPath()			const;
	QString		dbPathKort()		const;

	void		setDbPath(			QString newDbPath);

	
	QString		settingsCode() const;
	QUrl		envPicSource() const;
	QString		envPicError() const;
	
	void		setSettingsCode(const QString &newSettingsCode);
	void		setEnvPicSource(const QUrl &newEnvPicSource);
	void		setEnvPicError(const QString &newEnvPicError);
	
public slots:
	bool		selectDatabase(		const QString & path);
	bool		loadDatabase(		      QString   path = "");
	void		showData();
	void		showInFolder(		const QString & path);
	void		applySettings(		int width, int height);


signals:
	void		qmlsShownChanged();
	void		loadInQml(Labels * labels);
	void		showStackIndex(int idx);
	void		plotFilterNamesChanged();
	void		dbPathChanged();
	QString		rError();
	
	void		settingsChanged();
	void		envPicSourceChanged();
	void		envPicErrorChanged();
	QString		runRCommand(QString rCode);
	QString		runRCommands(QStringList rCode);
	
private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db					= nullptr;
	QStringList				_qmlsShown			= { "Environment", "Pedestrians", "Start"};
	Labels				*	_labels				= nullptr;
	QUrl					_envPicSource;
	QString					_dbPath,
							_envPicError,
							_settingsCode		= R"lovingC++2*(
predped::background(
	shape = rectangle(	center = c(4, 4), 	size = c(8, 8)),
	objects = 
		list(
			circle(		center = c(  4, 4),		radius = 1,			interactable = TRUE),
			rectangle(	center = c(1.5, 4),		size = c(1, 6),		interactable = TRUE),
			polygon(points = rbind(	c(3, 1),
									c(3, 2),
									c(6, 2),
									c(6, 6), 
									c(3, 6),
									c(3, 7),
									c(7, 7),
									c(7, 1)),
					interactable = TRUE)),
	entrance	= coordinate(c(0, 4)),
	exit		= coordinate(c(8, 4)),
	same_exit	= FALSE
)
)lovingC++2*";
	QSettings				_settings;
};

#endif // MAINMODEL_H
