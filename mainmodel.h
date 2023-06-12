#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "labels.h"
#include "schoolscannertable.h"

class Database;


class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList qmlsShown READ qmlsShown NOTIFY qmlsShownChanged)

public:
	explicit	MainModel(Database * db, QObject *parent = nullptr);

	QStringList qmlsShown() const;

public slots:
	bool		loadDatabase(const QString & dbPath);
	bool		selectDatabase();
	bool		testDatabase();


signals:
	void		qmlsShownChanged();
	void		loadInQml(Labels * labels, SchoolScannerTable * schoolTable);

private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db				= nullptr;

	QStringList				_qmlsShown		= { "Init" };

	Labels				*	_labels			= nullptr;
	SchoolScannerTable	*	_schoolTable	= nullptr;

};

#endif // MAINMODEL_H
