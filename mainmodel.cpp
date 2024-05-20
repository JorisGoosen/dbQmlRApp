#include "mainmodel.h"
#include "database.h"
#include <QFile>
#include <QUrl>
#include <QProcess>
#include <QDesktopServices>
#include <iostream>
#include <QDir>
#include "rwrapper.h"

MainModel::MainModel(Database * db, QObject *parent)
	: QObject{parent}, _db(db), _settings("GoosenAutomatisering", "Minds for Mobile Agents GUI")
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

	emit loadInQml(_labels);

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
		//setQmlsShown({"Analyse", "FilteredData", "Data", "Import"});
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
	const QStringList removeTheseUpFront = {"/",
											"file://"
#ifdef WIN32
											"/" //windows doesnt have a root
#endif
	};
	for(const QString & thisOne : removeTheseUpFront)
		if(newDbPath.startsWith(thisOne))
			newDbPath = newDbPath.right(newDbPath.size()-thisOne.size());
	newDbPath = QDir::toNativeSeparators(newDbPath);

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

void MainModel::applySettings()
{
	emit runRCommand(QString(R"GottaLoveThis(
	settings <- %1
	envPlot <- plot(setting, fill = "grey", color = "black", linewidth = 1.5)
	writeImage(plot=envPlot, plotFolder=".", plotFile = "envPlot.png", width = %2, height = %3, schaling = 1.0, backgroundColor = "transparent")
	
)GottaLoveThis").arg(_settingsCode.trimmed()).arg(1000).arg(1000));
	
	setEnvPicError(rError());
	static int localCounter = 0;
	if(envPicError().isEmpty())
		setEnvPicSource(QString("envPlot.png?%1").arg(localCounter++));
}

QString MainModel::settingsCode() const
{
	return _settingsCode;
}

void MainModel::setSettingsCode(const QString &newSettingsCode)
{
	if (_settingsCode == newSettingsCode)
		return;
	_settingsCode = newSettingsCode;
	emit settingsChanged();
}

QString MainModel::envPicSource() const
{
	return _envPicSource;
}

void MainModel::setEnvPicSource(const QString &newEnvPicSource)
{
	if (_envPicSource == newEnvPicSource)
		return;
	_envPicSource = newEnvPicSource;
	emit envPicSourceChanged();
}

QString MainModel::envPicError() const
{
	return _envPicError;
}

void MainModel::setEnvPicError(const QString &newEnvPicError)
{
	if (_envPicError == newEnvPicError)
		return;
	_envPicError = newEnvPicError;
	emit envPicErrorChanged();
}
