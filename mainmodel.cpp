#include "mainmodel.h"
#include "database.h"
#include <QFile>

MainModel::MainModel(Database * db, QObject *parent)
	: QObject{parent}, _db(db)
{

}

QStringList MainModel::qmlsShown() const
{
	return _qmlsShown;
}

bool MainModel::loadDatabase(const QString & dbPath)
{
	_db->setDbFile(std::filesystem::path(dbPath.toStdString()));

	_labels			= new Labels(_db);

	return true;
}

bool MainModel::selectDatabase()
{
	throw std::runtime_error("implement me");
}

bool MainModel::testDatabase()
{
	loadDatabase(":memory:");

	return true;
}

void MainModel::setQmlsShown(const QStringList & newQmlsShown)
{
	if (_qmlsShown == newQmlsShown)
		return;

	_qmlsShown = newQmlsShown;
	emit qmlsShownChanged();
}
