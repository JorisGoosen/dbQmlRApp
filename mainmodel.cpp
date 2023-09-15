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
	_schoolTable	= new SchoolScannerTable(_db);

	emit loadInQml(_labels, _schoolTable);

	return true;
}

bool MainModel::selectDatabase()
{
	loadDatabase("testing.sqlite");
}

bool MainModel::testDatabase()
{
	loadDatabase("testing.sqlite");

	if(_schoolTable->rowCount() > 0)
		setQmlsShown({"Import", "Data", "Analyse"});
	else
		setQmlsShown({"Import"});

	return true;
}

void MainModel::showData()
{
	if(!_qmlsShown.contains("Data"))
	{
		_qmlsShown.push_back("Data");
		_qmlsShown.push_back("Analyse");
		emit qmlsShownChanged();
	}

	emit showStackIndex(_qmlsShown.indexOf("Data"));
}

void MainModel::setQmlsShown(const QStringList & newQmlsShown)
{
	if (_qmlsShown == newQmlsShown)
		return;

	_qmlsShown = newQmlsShown;
	emit qmlsShownChanged();
}
