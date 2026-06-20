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
#include <QtWebEngineQuick/QtWebEngineQuick>
#include "mainmodel.h"
#include "respiro.h"
#include <QDir>
#include <QTimer>
#include <QQuickStyle>
#include <QThread>


int main(int argc, char *argv[])
{
	putenv("R_HOME=/Library/Frameworks/R.framework/Versions/Current/Resources");
	putenv("R_LIBS_USER=renv/library/macos/R-4.6/aarch64-apple-darwin23/");
	
	QGuiApplication				app(argc, argv);

	QCoreApplication::setOrganizationName(	"Biont Research");
	QCoreApplication::setOrganizationDomain("biontresearch.nl");
	QCoreApplication::setApplicationName(	"Respirometer");
	
	QtWebEngineQuick::initialize();

	QQmlApplicationEngine		mainEng;

	QQuickStyle::setStyle("Basic");

	MainModel					mainModel;
	Settings					settings;
	RWrapper					rWrapper;
	Respiro						respiro;

	QThread rThread;
	rWrapper.moveToThread(&rThread);
	rThread.start(QThread::Priority::NormalPriority);
	
	
	QObject::connect(&rWrapper,		&RWrapper::push_last_values,		&respiro,	&Respiro::receive_last_values	);
	QObject::connect(&rWrapper,		&RWrapper::push_meas_data,			&respiro,	&Respiro::push_meas_data,		Qt::QueuedConnection);
	QObject::connect(&rWrapper,		&RWrapper::push_proc_data,			&respiro,	&Respiro::push_proc_data,		Qt::QueuedConnection);
	QObject::connect(&rWrapper,		&RWrapper::push_current_channel,	&respiro,	&Respiro::push_current_channel	);
	QObject::connect(&rWrapper,		&RWrapper::push_valve_state,		&respiro,	&Respiro::push_valve_state		);
	QObject::connect(&rWrapper,		&RWrapper::push_vent_state,			&respiro,	&Respiro::push_vent_state		);
	QObject::connect(&rWrapper,		&RWrapper::push_pump_state,			&respiro,	&Respiro::push_pump_state		);
	QObject::connect(&rWrapper,		&RWrapper::push_O2_state,			&respiro,	&Respiro::push_O2_state			);
	QObject::connect(&rWrapper,		&RWrapper::push_CO2_state,			&respiro,	&Respiro::push_CO2_state		);
	QObject::connect(&rWrapper,		&RWrapper::push_CH4_state,			&respiro,	&Respiro::push_CH4_state		);
	QObject::connect(&rWrapper,		&RWrapper::push_error,				&respiro,	&Respiro::push_error			);
	QObject::connect(&rWrapper,		&RWrapper::push_warning,			&respiro,	&Respiro::push_warning			);
	QObject::connect(&rWrapper,		&RWrapper::push_info,				&respiro,	&Respiro::push_info				);
	QObject::connect(&rWrapper,		&RWrapper::push_datafilepath,		&respiro,	&Respiro::push_datafilepath		);
	QObject::connect(&rWrapper,		&RWrapper::push_loading_feedback,	&respiro,	&Respiro::push_loading_feedback	);
	QObject::connect(&rWrapper,		&RWrapper::flowChartPlotUpdated,	&respiro,	&Respiro::setFlowChartLocalFile	);
	QObject::connect(&rWrapper,		&RWrapper::choosePort,				&respiro,	&Respiro::choosePort,			Qt::QueuedConnection);
	QObject::connect(&rWrapper,		&RWrapper::setAvailablePorts,		&respiro,	&Respiro::setAvailablePorts,	Qt::QueuedConnection);

	QObject::connect(&respiro,		&Respiro::outputFolderChanged,		&rWrapper,	&RWrapper::setOutputFolder		);
	QObject::connect(&respiro,		&Respiro::instantPauseChanged,		&rWrapper,	&RWrapper::setInstantPause		);
	QObject::connect(&respiro,		&Respiro::delayedPauseChanged,		&rWrapper,	&RWrapper::setDelayedPause		);
	QObject::connect(&respiro,		&Respiro::controlWantedChanged,		&rWrapper,	&RWrapper::setControlWanted		);
	
	QObject::connect(&respiro,		&Respiro::leakTestsSignal,			&rWrapper,	&RWrapper::leakTestsRespiro		);
	QObject::connect(&respiro,		&Respiro::leakTestSignal,			&rWrapper,	&RWrapper::leakTestRespiro		);
	QObject::connect(&respiro,		&Respiro::startSignal,				&rWrapper,	&RWrapper::startRespiro			);
	QObject::connect(&respiro,		&Respiro::initSignal,				&rWrapper,	&RWrapper::initRespiro			);
	QObject::connect(&respiro,		&Respiro::initTestsSignal,			&rWrapper,	&RWrapper::initTestsRespiro		);
	
	QObject::connect(&respiro,		&Respiro::chosenPortChanged,		&rWrapper,	&RWrapper::setChosenPort,		Qt::QueuedConnection);
		
	QObject::connect(&respiro,		&Respiro::channelConfsChanged,		&mainModel,	&MainModel::inited,				Qt::QueuedConnection);
	QObject::connect(&respiro,		&Respiro::showLoading,				&mainModel,	&MainModel::modelsLoaded,		Qt::QueuedConnection);
	QObject::connect(&respiro,		&Respiro::respiroInited,			&mainModel,	&MainModel::respiroInited,		Qt::QueuedConnection);

	QObject::connect(&respiro,		&Respiro::allChanPlotChanged,		&mainModel,	&MainModel::enableHasPlot,		Qt::QueuedConnection);
	QObject::connect(&respiro,		&Respiro::measTimePlotChanged,		&mainModel,	&MainModel::enableHasPlot,		Qt::QueuedConnection);
	QObject::connect(&respiro,		&Respiro::groupChanPlotChanged,		&mainModel,	&MainModel::enableHasPlot,		Qt::QueuedConnection);
	QObject::connect(&respiro,		&Respiro::channelStatusChanged,		&mainModel,	&MainModel::enableHasPlot,		Qt::QueuedConnection);

	QObject::connect(&mainModel,	&MainModel::exitR,					&rWrapper,	&RWrapper::exitR,				Qt::DirectConnection);

	QTimer::singleShot(0, [&]()
	{
		RWrapper::singleton()->runRCommand("shareControllinoPorts()");
	});

	//Tell QML whatsup:
	mainEng.rootContext()->setContextProperty("outputFolder",		respiro.outputFolder());
	mainEng.rootContext()->setContextProperty("settings",			&settings);
	mainEng.rootContext()->setContextProperty("R",					&rWrapper);
	mainEng.rootContext()->setContextProperty("mainModel",			&mainModel);
	mainEng.rootContext()->setContextProperty("respiro",			&respiro);

	mainEng.rootContext()->setContextProperty("backgroundColor",		"black");
	mainEng.rootContext()->setContextProperty("foregroundColor",		"white");
	mainEng.rootContext()->setContextProperty("foregroundHColor",		"lightgrey");
	mainEng.rootContext()->setContextProperty("backgroundHColor",		"#222222");
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
		mainEng.rootContext()->setContextProperty("database",				respiro.db());
		mainEng.rootContext()->setContextProperty("respiroDataMeas",		respiro.dataMeas());
		mainEng.rootContext()->setContextProperty("respiroDataProc",		respiro.dataProc());
		mainEng.rootContext()->setContextProperty("respiroMsgs",			respiro.msgs());
		

		/*QFile	//rMain(		":/R/main.R"			),
				rWriteImage(":/R/writeImage.R"	);

		//rMain.open(			QIODeviceBase::ReadOnly);
		rWriteImage.open(	QIODeviceBase::ReadOnly);

		rWrapper.runRCommand(rWriteImage.readAll());
		*/
		//rWrapper.runRCommand(respiro.dataMeas()->dbplyrCode());
		//rWrapper.runRCommand(respiro.dataProc()->dbplyrCode());
		//rWrapper.runRCommand(respiro.msgs()->dbplyrCode());
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
