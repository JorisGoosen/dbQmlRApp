#ifndef MAINMODEL_H
#define MAINMODEL_H

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

public:
	explicit	MainModel(Database * db, QObject *parent = nullptr);

	QStringList qmlsShown()			const;
	QString		dbPath()			const;
	QString		dbPathKort()		const;

	void		setDbPath(			QString newDbPath);


public slots:
	bool		selectDatabase(		const QString & path);
	bool		loadDatabase(		      QString   path = "");
	void		showData();
	void		showInFolder(		const QString & path);


signals:
	void		qmlsShownChanged();
	void		loadInQml(Labels * labels);
	void		showStackIndex(int idx);
	void		plotFilterNamesChanged();
	void		dbPathChanged();

private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db					= nullptr;
	QStringList				_qmlsShown			= { "Environment", "Pedestrians", "StartSimulation" };
	Labels				*	_labels				= nullptr;
	QString					_dbPath;
	QSettings				_settings;
};

#endif // MAINMODEL_H
