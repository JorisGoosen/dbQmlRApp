#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <QSettings>
#include "labels.h"
#include "schoolscannertable.h"

class Database;


class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList	qmlsShown		READ qmlsShown										NOTIFY qmlsShownChanged			)
	Q_PROPERTY(QStringList	plotFilterNames	READ plotFilterNames	WRITE setPlotFilterNames	NOTIFY plotFilterNamesChanged	)
	Q_PROPERTY(QString		dbPath			READ dbPath				WRITE setDbPath				NOTIFY dbPathChanged			)
	Q_PROPERTY(QString		dbPathKort		READ dbPathKort										NOTIFY dbPathChanged			)

public:
	explicit	MainModel(Database * db, QObject *parent = nullptr);

	QStringList qmlsShown()			const;
	QStringList plotFilterNames()	const;
	QString		dbPath()			const;
	QString		dbPathKort()		const;

	void		setPlotFilterNames(	const QStringList & newPlotFilterNames);
	void		setDbPath(			const QString & newDbPath);

public slots:
	bool		selectDatabase(		const QString & path);
	bool		loadDatabase(		      QString   path = "");
	void		showData();


signals:
	void		qmlsShownChanged();
	void		loadInQml(Labels * labels, SchoolScannerTable * schoolTable);
	void		showStackIndex(int idx);
	void		plotFilterNamesChanged();
	void		dbPathChanged();

private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db					= nullptr;
	QStringList				_qmlsShown			= { "Welkom" },
							_plotFilterNames	= { "School", "Locatie", "Sector", "Niveau", "Leerjaar", "Klas", "Gender", "Cultuur" }; //ought to be same as PlotFilter

	Labels				*	_labels				= nullptr;
	SchoolScannerTable	*	_schoolTable		= nullptr;
	QString					_dbPath;
	QSettings				_settings;
};

#endif // MAINMODEL_H
