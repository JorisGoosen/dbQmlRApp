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
#include "importer.h"
#include "labels.h"
#include "mainmodel.h"
#include <QDir>
#include "schoolscannertable.h"
#include <QTimer>
#include <QQuickStyle>


int main(int argc, char *argv[])
{
	QGuiApplication				app(argc, argv);

	QCoreApplication::setOrganizationName(	"JorisGoosen");
	QCoreApplication::setOrganizationDomain("jorisgoosen.nl");
	QCoreApplication::setApplicationName(	"School Scanner");

	QQmlApplicationEngine		mainEng;

	QQuickStyle::setStyle("Basic");

	Database					database;
	MainModel					mainModel(&database);
	Settings					settings;
	RWrapper					rWrapper;


	QObject::connect(&mainModel, &MainModel::loadInQml, &mainEng, [&](Labels * labels, SchoolScannerTable * table)
	{
		Importer * importer = new Importer(table, labels);
		mainEng.rootContext()->setContextProperty("schoolScannerTable",			table);
		mainEng.rootContext()->setContextProperty("labels",						labels);
		mainEng.rootContext()->setContextProperty("importer",					importer);

	});

	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("settings",			&settings);
	mainEng.rootContext()->setContextProperty("R",					&rWrapper);
	mainEng.rootContext()->setContextProperty("database",			&database);
	mainEng.rootContext()->setContextProperty("mainModel",			&mainModel);


	mainEng.rootContext()->setContextProperty("backgroundColor",			"#BCE2D7");
	mainEng.rootContext()->setContextProperty("foregroundColor",			"white");
	mainEng.rootContext()->setContextProperty("windowBackgroundColor",		"grey");

	mainEng.rootContext()->setContextProperty("controlBackgroundDisabled",	"black");
	mainEng.rootContext()->setContextProperty("controlBackgroundNeutral",	"#FFF798");
	mainEng.rootContext()->setContextProperty("controlBackgroundFocus",		"white");
	mainEng.rootContext()->setContextProperty("controlBackgroundPressed",	"#DFD778");

	mainEng.rootContext()->setContextProperty("controlForegroundDisabled",	"pink");
	mainEng.rootContext()->setContextProperty("controlForegroundNeutral",	"black");
	mainEng.rootContext()->setContextProperty("controlForegroundFocus",		"black");
	mainEng.rootContext()->setContextProperty("controlForegroundPressed",	"#111");

	mainEng.rootContext()->setContextProperty("generalMargin",		20);

/*
	QFile	//rMain(		":/R/main.R"			),
			rWriteImage(":/R/writeImage.R"	);

	//rMain.open(			QIODeviceBase::ReadOnly);
	rWriteImage.open(	QIODeviceBase::ReadOnly);

	rWrapper.runRCommand(rWriteImage.readAll());
	rWrapper.runRCommand(mainTable.dbplyrCode());

	PlotRenderer piePlot	(QFile(":/R/pie.R"),	"pie.png");
	PlotRenderer linesPlot	(QFile(":/R/lines.R"), "lines.png");

	QObject::connect(&rWrapper, &RWrapper::plotWidthChanged,	&piePlot,	&PlotRenderer::setWidth);
	QObject::connect(&rWrapper, &RWrapper::plotWidthChanged,	&linesPlot, &PlotRenderer::setWidth);
	QObject::connect(&rWrapper, &RWrapper::plotHeightChanged,	&piePlot,	&PlotRenderer::setHeight);
	QObject::connect(&rWrapper, &RWrapper::plotHeightChanged,	&linesPlot, &PlotRenderer::setHeight);

	QObject::connect(&piePlot,		&PlotRenderer::runRCommand,		&rWrapper,	&RWrapper::runRCommand);
	QObject::connect(&linesPlot,	&PlotRenderer::runRCommand,		&rWrapper,	&RWrapper::runRCommand);

	mainEng.rootContext()->setContextProperty("piePlot",	&piePlot);
	mainEng.rootContext()->setContextProperty("linesPlot",	&linesPlot);

*/
	mainEng.load(":/main.qml");

	return app.exec();
}
