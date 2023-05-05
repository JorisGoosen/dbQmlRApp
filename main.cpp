// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4;  tab-width: 8; -*-
//
// Qt usage example for RInside, inspired by the standard 'density
// sliders' example for other GUI toolkits
//
// Copyright (C) 2011  Dirk Eddelbuettel and Romain Francois


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "rwrapper.h"
#include "database.h"
#include "tablemodel.h"

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

	mainTable.appendRows({{"Hello world!", 1, 10, 10.01, 101}, {"Well well...", 2, 20, 20.02, 202}});

	mainEng.rootContext()->setContextProperty("R",			&rWrapper);
	mainEng.rootContext()->setContextProperty("database",	&database);
	mainEng.rootContext()->setContextProperty("mainTable",	&mainTable);

	mainEng.load(":/main.qml");

    return app.exec();
}
