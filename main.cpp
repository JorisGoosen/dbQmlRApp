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
#include "labels.h"
#include "mainmodel.h"
#include <QDir>
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
	QCoreApplication::setApplicationName(	"Minds for Mobile Agents GUI");
#ifdef WIN32
	{
		QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
		if(!env.contains("R_HOME"))
			env.insert("R_HOME", "C:\\Program Files\\R\\R-4.4.0");

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

	QObject::connect(&mainModel, &MainModel::loadInQml, &mainEng, [&](Labels * labels)
	{

		mainEng.rootContext()->setContextProperty("labels",						labels);
		
		//QObject::connect(&rWrapper, &RWrapper::plotWidthChanged,		table,			&SchoolScannerTable::plotWidthChanged);
		//QObject::connect(&rWrapper, &RWrapper::plotHeightChanged,		table,			&SchoolScannerTable::plotHeightChanged);
		
		//table->initRStuff();

		plots.init();
	});

	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("settings",				&settings);
	mainEng.rootContext()->setContextProperty("R",						&rWrapper);
	mainEng.rootContext()->setContextProperty("database",				&database);
	mainEng.rootContext()->setContextProperty("mainModel",				&mainModel);
	mainEng.rootContext()->setContextProperty("plotList",				&plots);
	mainEng.rootContext()->setContextProperty("labels",					nullptr);
	
	mainEng.rootContext()->setContextProperty("fontFamilie",				"futura");
	mainEng.rootContext()->setContextProperty("dikkeLijnDikte",				4);
	mainEng.rootContext()->setContextProperty("backgroundColor",			"#000000");
	mainEng.rootContext()->setContextProperty("windowBackgroundColor",		"#111111");
	mainEng.rootContext()->setContextProperty("foregroundColor",			"#FFFF00");

	mainEng.rootContext()->setContextProperty("controlBackgroundDisabled",	"#000000");
	mainEng.rootContext()->setContextProperty("controlBackgroundNeutral",	"#000000");
	mainEng.rootContext()->setContextProperty("controlBackgroundFocus",		"#000000");
	mainEng.rootContext()->setContextProperty("controlBackgroundPressed",	"#000000");
	mainEng.rootContext()->setContextProperty("controlBackgroundPlots",		"#000000");

	mainEng.rootContext()->setContextProperty("controlForegroundDisabled",	"#666600");
	mainEng.rootContext()->setContextProperty("controlForegroundNeutral",	"#FFFF00");
	mainEng.rootContext()->setContextProperty("controlForegroundFocus",		"#FFFF99");
	mainEng.rootContext()->setContextProperty("controlForegroundPressed",	"#AAAA99");

	mainEng.rootContext()->setContextProperty("generalMargin",		20);

	mainEng.load(":/main.qml");

	return app.exec();
}
