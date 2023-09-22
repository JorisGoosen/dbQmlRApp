#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "labels.h"
#include "schoolscannertable.h"

class Database;


class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList qmlsShown		READ qmlsShown										NOTIFY qmlsShownChanged			)
	Q_PROPERTY(QStringList plotFilterNames	READ plotFilterNames	WRITE setPlotFilterNames	NOTIFY plotFilterNamesChanged	)

public:
	explicit	MainModel(Database * db, QObject *parent = nullptr);

	QStringList qmlsShown() const;

	QStringList plotFilterNames() const;
	void		setPlotFilterNames(const QStringList & newPlotFilterNames);

public slots:
	bool		loadDatabase(const QString & dbPath);
	bool		selectDatabase();
	bool		testDatabase();
	void		showData();


signals:
	void		qmlsShownChanged();
	void		loadInQml(Labels * labels, SchoolScannerTable * schoolTable);
	void		showStackIndex(int idx);

	void plotFilterNamesChanged();

private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db					= nullptr;

	QStringList				_qmlsShown			= { "Init" },
							_plotFilterNames	= { "School", "Locatie", "Sector", "Niveau", "Leerjaar", "Klas", "Gender", "Cultuur" }; //ought to be PlotFilter

	Labels				*	_labels				= nullptr;
	SchoolScannerTable	*	_schoolTable		= nullptr;
};

#endif // MAINMODEL_H
