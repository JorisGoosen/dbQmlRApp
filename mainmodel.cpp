#include "mainmodel.h"
#include "database.h"
#include <QFile>
#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#include <iostream>
#include <QDir>

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

	std::cerr<< "MainModel::loadDatabase krijgt " << path.toStdString() << std::endl;

	_db->setDbFile(std::filesystem::path(path.toStdString()));

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
	setDbPath(QUrl::fromLocalFile(path).toLocalFile());
	return loadDatabase();
}

void MainModel::showData()
{
	if(!_qmlsShown.contains("Data"))
	{
		setQmlsShown({"Analyse", "FilteredData", "Data", "Import"});
		emit qmlsShownChanged();
	}

	//_schoolTable->renderPlots();
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

void MainModel::setDbPath(QString newDbPath)
{
#ifdef WIN32
	const QStringList removeTheseUpFront = {"/", "file:///"};
	for(const QString & thisOne : removeTheseUpFront)
		if(newDbPath.startsWith(thisOne))
			newDbPath = newDbPath.right(newDbPath.size()-thisOne.size());
	newDbPath = QDir::toNativeSeparators(newDbPath);
#endif

	std::cerr << "MainModel::setDbPath('" << newDbPath.toStdString() << "'" << std::endl;

	if (_dbPath == newDbPath)
		return;
	_dbPath = newDbPath;
	emit dbPathChanged();

	_settings.setValue("dbPath", _dbPath);
}

//Thanks https://stackoverflow.com/a/46019091
void MainModel::showInFolder(const QString& path)
{
	QFileInfo info(path);
#if defined(Q_OS_WIN)
	QStringList args;
	if (!info.isDir())
		args << "/select,";
	args << QDir::toNativeSeparators(path);
	if (QProcess::startDetached("explorer", args))
		return;
#elif defined(Q_OS_MAC)
	QStringList args;
	args << "-e" << "tell application \"Finder\"";
	args << "-e" << "activate";
	args << "-e" << "select POSIX file \"" + path + "\"";
	args << "-e" << "end tell";
	args << "-e" << "return";
	if (!QProcess::execute("/usr/bin/osascript", args))
		return;
#endif
	QDesktopServices::openUrl(QUrl::fromLocalFile(info.isDir()? path : info.path()));
}
