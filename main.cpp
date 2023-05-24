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
#include "tablemodel.h"
#include "settings.h"
#include "plotrenderer.h"
#include <QDir>
#include <QTimer>

int main(int argc, char *argv[])
{
	QGuiApplication				app(argc, argv);

	QCoreApplication::setOrganizationName(	"JorisGoosen");
	QCoreApplication::setOrganizationDomain("jorisgoosen.nl");
	QCoreApplication::setApplicationName(	"dbQmlRApp");

	QQmlApplicationEngine		mainEng;

	Settings					settings;
	RWrapper					rWrapper;
	Database					database("qmlR.sqlite");

	//Create table, with columnsdefs:
	typedef ColumnDefinition	CD;
	ColumnDefinitions			mainColumns = {
		new CD("Hello", "hello",	ColumnType::Text),
		new CD("World", "world",	ColumnType::DateTime),
		new CD("This",	"this",		ColumnType::Duration),
		new CD("is a",	"isa",		ColumnType::NumDbl),
		new CD("table", "tafel",	ColumnType::NumInt)
	};
	TableModel					mainTable(&database, "HelloWorld",	mainColumns);

	//Some dummy data:
	mainTable.appendRows({
							 {"Hello world!",	1,	  1,	10.01,		arc4random()%256},
							 {"Well well...",	2,	  2,	20.0332,	arc4random()%256},
							 {"Hello world!",	3,	  4,	30.03,		arc4random()%256},
							 {"Hello world!",	4,	  8,	10.014,		arc4random()%256},
							 {"Hello world!",	5,	 16,	120.035,	arc4random()%256},
							 {"Hello world!",	6,	 32,	160.06,		arc4random()%256},
							 {"Well well...",	7,	 64,	120.32107,	arc4random()%256},
							 {"Well well...",	8,	128,	250.02,		arc4random()%256},
							 {"Well well...",	9,	256,	210.02,		arc4random()%256},
							 {"And 3rd!",		10, 512,	123.03,		arc4random()%256}
						 });

	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("settings",	&settings);
	mainEng.rootContext()->setContextProperty("R",			&rWrapper);
	mainEng.rootContext()->setContextProperty("database",	&database);
	mainEng.rootContext()->setContextProperty("mainTable",	&mainTable);

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


	mainEng.load(":/main.qml");

	return app.exec();
}
