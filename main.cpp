// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4;  tab-width: 8; -*-
//
// Qt usage example for RInside, inspired by the standard 'density
// sliders' example for other GUI toolkits
//
// Copyright (C) 2011  Dirk Eddelbuettel and Romain Francois


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include "rwrapper.h"
#include "database.h"
#include "settings.h"
#include "plotrenderer.h"
#include "plotrenderers.h"
#include "importer.h"
#include "labels.h"
#include "mainmodel.h"
#include <QDir>
#include "schoolscannertable.h"
#include <QTimer>
#include <QQuickStyle>
#ifdef WIN32
#include <QStandardPaths>
#include <QProcessEnvironment>
#endif


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, ".UTF8");
	QGuiApplication				app(argc, argv);

	QCoreApplication::setOrganizationName(	"JorisGoosen");
	QCoreApplication::setOrganizationDomain("jorisgoosen.nl");
	QCoreApplication::setApplicationName(	"School Scanner");
#ifdef WIN32
	{
		QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
		if(!env.contains("R_HOME"))
			env.insert("R_HOME", "C:\\Program Files\\R\\R-4.3.1");

		env.insert("PATH", env.value("R_HOME") + "\\bin\\x64;" + env.value("PATH"));


		if(!env.contains("R_LIBS_USER"))
			env.insert("R_LIBS_USER", QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)) + "\\..\\R\\win-library\\4.3");
		env.insert("R_LIBS",  env.value("R_LIBS_USER") + ";" + env.value("R_HOME") + "\\library");

/*		std::cerr << "R_HOME=" << env.value("R_HOME").toStdString() <<
			"\nR_LIBS=" << env.value("R_LIBS").toStdString() <<
			"\nPATH=" << env.value("PATH").toStdString() <<std::endl;*/
	}
#endif
	QQmlApplicationEngine		mainEng;

	QQuickStyle::setStyle("Basic");

	Database					database;
	MainModel					mainModel(&database);
	Settings					settings;
	RWrapper					rWrapper;
	PlotRenderers				plots;

	rWrapper.runRCommand("print(paste0('Sys.getenv(R_LIBS_USER)', Sys.getenv('R_LIBS_USER'))); print(paste0('.libPaths()=', .libPaths())); ");

	{
		QFile	mainRFile(":/R/main.R");
		mainRFile.open(QIODeviceBase::ReadOnly);
		QString str = mainRFile.readAll();
		mainRFile.close();

		rWrapper.runRCommand(str);
	}

	QObject::connect(&plots,	&PlotRenderers::runRCommand,	&rWrapper,		&RWrapper::runRCommand);
	QObject::connect(&plots,	&PlotRenderers::runRCommands,	&rWrapper,		&RWrapper::runRCommands);

	QObject::connect(&mainModel, &MainModel::loadInQml, &mainEng, [&](Labels * labels, SchoolScannerTable * table)
	{

		Importer * importer = new Importer(table, labels);
		mainEng.rootContext()->setContextProperty("schoolScannerTable",			table);
		mainEng.rootContext()->setContextProperty("labels",						labels);
		mainEng.rootContext()->setContextProperty("importer",					importer);

		QObject::connect(table,		&SchoolScannerTable::addContextProperty,	[&](const QString & name, QObject * object){ mainEng.rootContext()->setContextProperty(name, object); });

		QObject::connect(importer,	&Importer::showData,				&mainModel,		&MainModel::showData);
		QObject::connect(&rWrapper, &RWrapper::plotWidthChanged,		table,			&SchoolScannerTable::plotWidthChanged);
		QObject::connect(&rWrapper, &RWrapper::plotHeightChanged,		table,			&SchoolScannerTable::plotHeightChanged);
		QObject::connect(table,		&SchoolScannerTable::runRCommand,	&rWrapper,		&RWrapper::runRCommand);
		QObject::connect(table,		&SchoolScannerTable::renderPlots,	&plots,			&PlotRenderers::renderPlots,	Qt::QueuedConnection);

		table->initRStuff();

		plots.init();
	});

	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("settings",				&settings);
	mainEng.rootContext()->setContextProperty("R",						&rWrapper);
	mainEng.rootContext()->setContextProperty("database",				&database);
	mainEng.rootContext()->setContextProperty("mainModel",				&mainModel);
	mainEng.rootContext()->setContextProperty("plotList",				&plots);
	mainEng.rootContext()->setContextProperty("schoolScannerTable",		nullptr);
	mainEng.rootContext()->setContextProperty("labels",					nullptr);
	mainEng.rootContext()->setContextProperty("importer",				nullptr);
	mainEng.rootContext()->setContextProperty("plotPie",				nullptr);

	QMap<QString, QString> kleurenCM =
	{
		{	"rozig",		"#EF2560"	},
		{	"lichtrozig",	"#f6b6cc"	},
		{	"lichtblauwig",	"#9CCDD1"	},
		{	"blauwig",		"#038794"	},
		{	"zwartig",		"#1D1D1B"	},
		{	"lichtgroen",	"#BCE2D7"	},
		{	"donkergroen",	"#5FA48F"	},
		{	"lichtgeel",	"#FFF798"	},
		{	"witgroen",		"#cdf3e8"	},
	};

	mainEng.rootContext()->setContextProperty("fontFamilie",				"karla");
	mainEng.rootContext()->setContextProperty("dikkeLijnDikte",				4);
	mainEng.rootContext()->setContextProperty("backgroundColor",			kleurenCM["lichtblauwig"]);
	mainEng.rootContext()->setContextProperty("windowBackgroundColor",		kleurenCM["blauwig"]);
	mainEng.rootContext()->setContextProperty("foregroundColor",			kleurenCM["rozig"]);

	mainEng.rootContext()->setContextProperty("controlBackgroundDisabled",	kleurenCM["lichtblauwig"]);
	mainEng.rootContext()->setContextProperty("controlBackgroundNeutral",	kleurenCM["blauwig"]);
	mainEng.rootContext()->setContextProperty("controlBackgroundFocus",		kleurenCM["lichtgroen"]);
	mainEng.rootContext()->setContextProperty("controlBackgroundPressed",	kleurenCM["donkergroen"]);
	mainEng.rootContext()->setContextProperty("controlBackgroundPlots",		kleurenCM["witgroen"]);

	mainEng.rootContext()->setContextProperty("controlForegroundDisabled",	kleurenCM["zwartig"]);
	mainEng.rootContext()->setContextProperty("controlForegroundNeutral",	kleurenCM["lichtgeel"]);
	mainEng.rootContext()->setContextProperty("controlForegroundFocus",		kleurenCM["rozig"]);
	mainEng.rootContext()->setContextProperty("controlForegroundPressed",	kleurenCM["zwartig"]);

	mainEng.rootContext()->setContextProperty("generalMargin",		20);

	mainEng.load(":/main.qml");

	return app.exec();
}
