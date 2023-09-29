#include "mainmodel.h"
#include "database.h"
#include <QFile>
#include <QUrl>

MainModel::MainModel(Database * db, QObject *parent)
	: QObject{parent}, _db(db), _settings("GoosenAutomatisering", "School Scanner")
{
	_dbPath = _settings.value("dbPath").toString();
}

QStringList MainModel::qmlsShown() const
{
	return _qmlsShown;
}

bool MainModel::loadDatabase(QString path)
{
	if(path == "")
		path = _dbPath;

	if(path == "")
		return false;

	_db->setDbFile(std::filesystem::path(QUrl(path).toString(QUrl::RemoveScheme).toStdString()));

	_labels			= new Labels(_db);
	_schoolTable	= new SchoolScannerTable(_db);

	emit loadInQml(_labels, _schoolTable);

	if(_schoolTable->rowCount() > 0)
		setQmlsShown({"Analyse", "FilteredData", "Data", "Import"});
	else
		setQmlsShown({"Import"});

	return true;
}

bool MainModel::selectDatabase(const QString & path)
{
	setDbPath(path);
	return loadDatabase();
}

void MainModel::showData()
{
	if(!_qmlsShown.contains("Data"))
	{
		setQmlsShown({"Analyse", "FilteredData", "Data", "Import"});
		emit qmlsShownChanged();
	}

	_schoolTable->renderPlots();
}

void MainModel::setQmlsShown(const QStringList & newQmlsShown)
{
	if (_qmlsShown == newQmlsShown)
		return;

	_qmlsShown = newQmlsShown;
	emit qmlsShownChanged();
}

QStringList MainModel::plotFilterNames() const
{
	return _plotFilterNames;
}

void MainModel::setPlotFilterNames(const QStringList & newPlotFilterNames)
{
	if (_plotFilterNames == newPlotFilterNames)
		return;
	_plotFilterNames = newPlotFilterNames;
	emit plotFilterNamesChanged();
}

QString MainModel::dbPath() const
{
	return _dbPath;
}

QString MainModel::dbPathKort() const
{
	const qsizetype maxL = 40;

	if(_dbPath.size() < maxL)
		return _dbPath;

	return "..." + _dbPath.right(maxL);
}

void MainModel::setDbPath(const QString & newDbPath)
{
	if (_dbPath == newDbPath)
		return;
	_dbPath = newDbPath;
	emit dbPathChanged();

	_settings.setValue("dbPath", _dbPath);
}
