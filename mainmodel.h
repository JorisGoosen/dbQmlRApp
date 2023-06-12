#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "labels.h"

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

private:
	void		setQmlsShown(const QStringList & newQmlsShown);

	Database			*	_db				= nullptr;

	QStringList				_qmlsShown		= { "Init" };

	Labels				*	_labels			= nullptr;

};

#endif // MAINMODEL_H
