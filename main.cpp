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
#include "mainmodel.h"
#include "respiro.h"
#include <QDir>
#include <QTimer>
#include <QQuickStyle>
#include <QThread>


int main(int argc, char *argv[])
{
	QGuiApplication				app(argc, argv);

	QCoreApplication::setOrganizationName(	"JorisGoosen");
	QCoreApplication::setOrganizationDomain("jorisgoosen.nl");
	QCoreApplication::setApplicationName(	"School Scanner");

	QQmlApplicationEngine		mainEng;

	QQuickStyle::setStyle("Basic");

	MainModel					mainModel;
	Settings					settings;
	RWrapper					rWrapper;
	Respiro						respiro;

	QThread rThread;
	rWrapper.moveToThread(&rThread);
	rThread.start();

	QObject::connect(&rWrapper,	&RWrapper::push_raw_data,			&respiro,	&Respiro::push_raw_data			);
	QObject::connect(&rWrapper,	&RWrapper::push_current_channel,	&respiro,	&Respiro::push_current_channel	);
	QObject::connect(&rWrapper,	&RWrapper::push_valve_state,		&respiro,	&Respiro::push_valve_state		);
	QObject::connect(&rWrapper,	&RWrapper::push_pump_state,			&respiro,	&Respiro::push_pump_state		);
	QObject::connect(&rWrapper,	&RWrapper::push_o2_state,			&respiro,	&Respiro::push_o2_state			);
	QObject::connect(&rWrapper,	&RWrapper::push_co2_state,			&respiro,	&Respiro::push_co2_state		);
	QObject::connect(&rWrapper,	&RWrapper::push_ch4_state,			&respiro,	&Respiro::push_ch4_state		);
	QObject::connect(&rWrapper,	&RWrapper::push_error,				&respiro,	&Respiro::push_error			);
	QObject::connect(&rWrapper,	&RWrapper::push_warning,			&respiro,	&Respiro::push_warning			);
	QObject::connect(&rWrapper,	&RWrapper::push_info,				&respiro,	&Respiro::push_info				);
	QObject::connect(&rWrapper,	&RWrapper::push_loading_feedback,	&respiro,	&Respiro::push_loading_feedback	);

	QObject::connect(&respiro,	&Respiro::outputFolderChanged,		&rWrapper,	&RWrapper::setOutputFolder		);
	QObject::connect(&respiro,	&Respiro::instantPauseChanged,		&rWrapper,	&RWrapper::setInstantPause		);
	QObject::connect(&respiro,	&Respiro::delayedPauseChanged,		&rWrapper,	&RWrapper::setDelayedPause		);
	QObject::connect(&respiro,	&Respiro::controlWantedChanged,		&rWrapper,	&RWrapper::setControlWanted		);
	QObject::connect(&respiro,	&Respiro::start,					&rWrapper,	&RWrapper::startRespiro			);

	QObject::connect(&respiro,	&Respiro::modelsLoaded,				&mainModel,	&MainModel::modelsLoaded,		Qt::QueuedConnection);


	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("outputFolder",		respiro.outputFolder());
	mainEng.rootContext()->setContextProperty("settings",			&settings);
	mainEng.rootContext()->setContextProperty("R",					&rWrapper);
	mainEng.rootContext()->setContextProperty("mainModel",			&mainModel);
	mainEng.rootContext()->setContextProperty("respiro",			&respiro);

	mainEng.rootContext()->setContextProperty("backgroundColor",		"black");
	mainEng.rootContext()->setContextProperty("foregroundColor",		"white");
	mainEng.rootContext()->setContextProperty("foregroundHColor",		"lightgrey");
	mainEng.rootContext()->setContextProperty("windowBackgroundColor",	"grey");

	mainEng.rootContext()->setContextProperty("controlBackgroundNeutral",	"lightgrey");
	mainEng.rootContext()->setContextProperty("controlBackgroundFocus",		"white");
	mainEng.rootContext()->setContextProperty("controlBackgroundPressed",	"black");
	mainEng.rootContext()->setContextProperty("controlForegroundNeutral",	"black");
	mainEng.rootContext()->setContextProperty("controlForegroundFocus",		"black");
	mainEng.rootContext()->setContextProperty("controlForegroundPressed",	"white");

	mainEng.rootContext()->setContextProperty("generalMargin",		20);

	auto respiroModelsLoadedHandler = [&]()
	{
		mainEng.rootContext()->setContextProperty("database",			respiro.db());
		mainEng.rootContext()->setContextProperty("labels",				respiro.labels());
		mainEng.rootContext()->setContextProperty("respiroData",		respiro.data());
		mainEng.rootContext()->setContextProperty("respiroMsgs",		respiro.msgs());

		/*QFile	//rMain(		":/R/main.R"			),
				rWriteImage(":/R/writeImage.R"	);

		//rMain.open(			QIODeviceBase::ReadOnly);
		rWriteImage.open(	QIODeviceBase::ReadOnly);

		rWrapper.runRCommand(rWriteImage.readAll());
		*/
		rWrapper.runRCommand(respiro.data()->dbplyrCode());
		rWrapper.runRCommand(respiro.msgs()->dbplyrCode(false));
	};

	QObject::connect(&respiro, &Respiro::modelsLoaded, respiroModelsLoadedHandler);



	/*PlotRenderer piePlot	(QFile(":/R/pie.R"),	"pie.png");
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

	int returnCode = app.exec();

	rThread.quit();
	rThread.wait();

	return returnCode;
}
