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
#include <QDir>
#include <QTimer>

int main(int argc, char *argv[])
{
	QGuiApplication				app(argc, argv);

	QQmlApplicationEngine		mainEng;

	RWrapper					rWrapper;
	Database					database("qmlR.sqlite");
	typedef ColumnDefinition	CD;
	ColumnDefinitions			mainColumns = {
		new CD("Hello", "hello",	ColumnType::Text),
		new CD("World", "world",	ColumnType::DateTime),
		new CD("This",	"this",		ColumnType::Duration),
		new CD("is a",	"isa",		ColumnType::NumDbl),
		new CD("table", "tafel",	ColumnType::NumInt)
	};
	TableModel					mainTable(&database, "HelloWorld",	mainColumns);

	mainTable.appendRows({
							 {"Hello world!",	1,	  1,	10.01,		arc4random()%256},
							 {"Well well...",	2,	  2,	20.0332,	arc4random()%256},
							 {"Hello world!",	3,	  4,	30.03,		arc4random()%256},
							 {"Hello world!",	4,	  8,	10.014,		arc4random()%256},
							 {"Hello world!",	5,	 16,	120.035,	arc4random()%256},
							 {"Hello world!",	6,	 32,	160.06,		arc4random()%256},
							 {"Well well...",	7,	 64,	120.32107,	arc4random()%256},
							 {"Well well...",	8,	128,	250.02,		arc4random()%256},
							 {"Well well...",	9,	256,	210.02,	arc4random()%256},
							 {"And 3rd!",		10, 512,	123.03,	arc4random()%256}
						 });

	mainEng.rootContext()->setContextProperty("R",			&rWrapper);
	mainEng.rootContext()->setContextProperty("database",	&database);
	mainEng.rootContext()->setContextProperty("mainTable",	&mainTable);
	mainEng.rootContext()->setContextProperty("plots",		QStringList({"pie.png", "lines.png"}));

	QFile	rMain(		":/R/main.R"			),
			rWriteImage(":/R/writeImage.R"	);

	rMain.open(			QIODeviceBase::ReadOnly);
	rWriteImage.open(	QIODeviceBase::ReadOnly);

	rWrapper.runRCommand(rWriteImage.readAll());
	rWrapper.runRCommand(mainTable.dbplyrCode());

	QString mainCode = rMain.readAll();

	auto runMainCode = [&]()
	{
		static int w = 0, h = 0;

		if(w != rWrapper.plotWidth() || h != rWrapper.plotHeight())
		{
			rWrapper.runRCommand("WIDTH  <- " + QString::number(rWrapper.plotWidth())  + ";\n" +
								 "HEIGHT <- " + QString::number(rWrapper.plotHeight()) + ";\n" +
								 mainCode);

			mainEng.rootContext()->setContextProperty("plots",		QStringList({}));
			QTimer::singleShot(10, [&](){ mainEng.rootContext()->setContextProperty("plots",		QStringList({"pie.png", "lines.png"})); });
		}

		w = rWrapper.plotWidth();
		h = rWrapper.plotHeight();
	};

	runMainCode();

	QTimer delayR;
	delayR.setInterval(100);
	delayR.setSingleShot(false);
	delayR.callOnTimeout(runMainCode);

	QObject::connect(&rWrapper, &RWrapper::plotWidthChanged,	&delayR,	qOverload<>(&QTimer::start));
	QObject::connect(&rWrapper, &RWrapper::plotHeightChanged,	&delayR,	qOverload<>(&QTimer::start));

	mainEng.rootContext()->setContextProperty("plotFolder",	QDir::currentPath());


	mainEng.load(":/main.qml");

	return app.exec();
}
