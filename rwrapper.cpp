#include "rwrapper.h"
#include <QThread>

RWrapper * RWrapper::_singleton = nullptr;

RWrapper::RWrapper(QObject *parent)
	: QObject{parent}, R(new RInside(0, nullptr, true, true, false))
{
	assert(!_singleton);
	_singleton = this;

	(*R)["respiroGui_push_current_channel"]			= Rcpp::InternalFunction(&respiroGui_push_current_channel);
	(*R)["respiroGui_push_last_values"]				= Rcpp::InternalFunction(&respiroGui_push_last_values);
	(*R)["respiroGui_push_valve_state"]				= Rcpp::InternalFunction(&respiroGui_push_valve_state);
	(*R)["respiroGui_push_pump_state"]				= Rcpp::InternalFunction(&respiroGui_push_pump_state);
	(*R)["respiroGui_push_meas_data"]				= Rcpp::InternalFunction(&respiroGui_push_meas_data);
	(*R)["respiroGui_push_proc_data"]				= Rcpp::InternalFunction(&respiroGui_push_proc_data);
	(*R)["respiroGui_push_co2_state"]				= Rcpp::InternalFunction(&respiroGui_push_co2_state);
	(*R)["respiroGui_push_ch4_state"]				= Rcpp::InternalFunction(&respiroGui_push_ch4_state);
	(*R)["respiroGui_push_o2_state"]				= Rcpp::InternalFunction(&respiroGui_push_o2_state);
	(*R)["respiroGui_push_status"]					= Rcpp::InternalFunction(&respiroGui_push_status);
	(*R)["respiroGui_push_error"]					= Rcpp::InternalFunction(&respiroGui_push_error);
	(*R)["respiroGui_push_plot"]					= Rcpp::InternalFunction(&respiroGui_push_plot);
	(*R)["respiroGui_push_info"]					= Rcpp::InternalFunction(&respiroGui_push_info);
	(*R)["respiroGui_push_warning"]					= Rcpp::InternalFunction(&respiroGui_push_warning);
	(*R)["respiroGui_push_datafilepath"]			= Rcpp::InternalFunction(&respiroGui_push_datafilepath);
	(*R)["respiroGui_poll_instant_pause"]			= Rcpp::InternalFunction(&respiroGui_poll_instant_pause);
	(*R)["respiroGui_poll_delayed_pause"]			= Rcpp::InternalFunction(&respiroGui_poll_delayed_pause);
	(*R)["respiroGui_poll_control_wanted"]			= Rcpp::InternalFunction(&respiroGui_poll_control_wanted);
	(*R)["respiroGui_push_loading_feedback"]		= Rcpp::InternalFunction(&respiroGui_push_loading_feedback);
	(*R)["respiroGui_update_flow_diagram"]			= Rcpp::InternalFunction(&respiroGui_update_flow_diagram);
	(*R)["respiroGui_ask_which_port"]				= Rcpp::InternalFunction(&respiroGui_ask_which_port);

	
	

	runRCommand("print(R.home())");
	runRCommand("source(paste0(getwd(), '/renv/activate.R'))");
	runRCommand("library(respiro)");
}

QString RWrapper::runRCommand(QString command)
{
	std::cout << "Running R command:\n" << command.toStdString() << std::endl;

	RInside::Proxy res = R->parseEvalNT(command.toStdString());

	std::function<QString(SEXP sexp)> f;

	f = [&](SEXP res)
	{
		QStringList out;

		if(!res)
			out.append("NULL");
		else if(Rf_isNull(res))
			out.append("NULL");
		else if(Rf_isString(res))
			for(Rcpp::String str : Rcpp::StringVector(res))
				out.append(QString::fromStdString(str));
		else if(Rf_isInteger(res))
			for(int r : Rcpp::IntegerVector(res))
				out.append(QString::number(r));
		else if(Rf_isReal(res))
			for(double r : Rcpp::DoubleVector(res))
				out.append(QString::number(r));
		else if(Rf_isList(res))
			for(SEXP s : Rcpp::List(res))
				out.append(f(s));
		else
			out.append("???");


		return out.join("\n");
	};

	QString outQ = f(res);

	std::cout << ": " << outQ.toStdString() << std::endl;

	_prevOutput.append(outQ);
	emit prevOutputChanged();

	return outQ;
}

QStringList RWrapper::prevOutput() const
{
	return _prevOutput;
}

void RWrapper::setPrevOutput(const QStringList & newPrevOutput)
{
	if (_prevOutput == newPrevOutput)
		return;

	_prevOutput = newPrevOutput;
	emit prevOutputChanged();
}

int RWrapper::plotWidth() const
{
	return std::max(10, _plotWidth);
}

void RWrapper::setPlotWidth(int newPlotWidth)
{
	if (_plotWidth == newPlotWidth)
		return;

	_plotWidth = newPlotWidth;
	emit plotWidthChanged(_plotWidth);
}

int RWrapper::plotHeight() const
{
	return std::max(10, _plotHeight);
}

void RWrapper::setPlotHeight(int newPlotHeight)
{
	if (_plotHeight == newPlotHeight)
		return;

	_plotHeight = newPlotHeight;
	emit plotHeightChanged(_plotHeight);
}

void respiroGui_push_meas_data()
{
	emit RWrapper::singleton()->push_meas_data();
}


void respiroGui_push_proc_data()
{
	emit RWrapper::singleton()->push_proc_data();
}


void respiroGui_push_last_values( int relTime, int measuring_channel, float pressure, float flow, float temperatureRespirometer, float temperatureSample, float CO2_ADC, float O2_raw, float CH4_raw, float CO2_raw)
{
	emit RWrapper::singleton()->push_last_values(relTime, measuring_channel, pressure, flow, temperatureRespirometer, temperatureSample, CO2_ADC, O2_raw, CH4_raw, CO2_raw);
}


void respiroGui_push_current_channel(	int			channel)
{
	emit RWrapper::singleton()->push_current_channel(channel);
}

void respiroGui_push_valve_state(		int			channel, bool valve_open)
{
	emit RWrapper::singleton()->push_valve_state(channel, valve_open);
}


void respiroGui_push_vent_state(int id, bool vent_on)
{
	emit RWrapper::singleton()->push_vent_state(id, vent_on);
}

void respiroGui_push_pump_state( bool		pump_on)
{
	emit RWrapper::singleton()->push_pump_state(pump_on);
}

void respiroGui_push_o2_state(			bool		O2_on)
{
	emit RWrapper::singleton()->push_O2_state(O2_on);
}

void respiroGui_push_co2_state(			bool		CO2_on)
{
	emit RWrapper::singleton()->push_CO2_state(CO2_on);
}

void respiroGui_push_ch4_state(			bool		CH4_on)
{
	emit RWrapper::singleton()->push_CH4_state(CH4_on);
}

void respiroGui_push_error(				std::string	error)
{
	emit RWrapper::singleton()->push_error(QString::fromStdString(error));
}

void respiroGui_push_warning(			std::string	warning)
{
	emit RWrapper::singleton()->push_warning(QString::fromStdString(warning));
}

void respiroGui_push_info(std::string info)
{
	emit RWrapper::singleton()->push_info(QString::fromStdString(info));
}

void respiroGui_push_datafilepath(std::string datafile)
{
	emit RWrapper::singleton()->push_datafilepath(QString::fromStdString(datafile));
}

bool respiroGui_poll_instant_pause()
{
	return RWrapper::singleton()->instantPause();
}

bool respiroGui_poll_delayed_pause()
{
	return RWrapper::singleton()->delayedPause();
}

bool respiroGui_poll_control_wanted()
{
	return RWrapper::singleton()->controlWanted();
}

void respiroGui_push_loading_feedback(std::string feedback, bool finished, std::string errorMsg)
{
	emit RWrapper::singleton()->push_loading_feedback(QString::fromStdString(feedback), finished, QString::fromStdString(errorMsg));
}

void respiroGui_update_flow_diagram(std::string png)
{
	emit RWrapper::singleton()->flowChartPlotUpdated(QString::fromStdString(png));
}

std::string respiroGui_ask_which_port(Rcpp::CharacterVector ports)
{
	auto		stdports = Rcpp::as<std::vector<std::string>>(ports);
	QStringList qports;

	for(auto & p : stdports)
		qports.append(QString::fromStdString(p));

	return (RWrapper::singleton()->waitForPortChoice(qports)).toStdString();
}

bool RWrapper::instantPause() const
{
	return _instantPause;
}

void RWrapper::setInstantPause(bool newInstantPause)
{
	if (_instantPause == newInstantPause)
		return;
	_instantPause = newInstantPause;
	emit instantPauseChanged();
}

bool RWrapper::delayedPause() const
{
	return _delayedPause;
}

void RWrapper::setDelayedPause(bool newDelayedPause)
{
	if (_delayedPause == newDelayedPause)
		return;
	_delayedPause = newDelayedPause;
	emit delayedPauseChanged();
}

bool RWrapper::controlWanted() const
{
	return _controlWanted;
}

void RWrapper::setControlWanted(bool newControlWanted)
{
	if (_controlWanted == newControlWanted)
		return;
	_controlWanted = newControlWanted;
	emit controlWantedChanged();
}

void RWrapper::initRespiro(QString datafile, QList<int> channels)
{
	(*R)[".dataFile"]			= datafile.toStdString();
	(*R)[".outputFolder"]		= _outputFolder.toStdString();
		
	const QString channelsStr = [channels](){ QStringList l; for(int channel : channels) l.append(QString::number(channel)); return ("c(" + l.join(",") + ")"); }();

	const QString initRespiroR =
			"setwd(.outputFolder)\n"
			"library(respiro)\n"
			"rc = NULL\n"
			".channels = " + channelsStr  + "\n"
			"withCallingHandlers(\n{\n"
			"  rc = RespiroControl$new(channels=.channels" + QString(datafile != "" ? ", dataFile=.dataFile" : "")+", connectControllino=" + (datafile == "" ? "TRUE" : "FALSE") +")\n"
			"\n},error=function(error) { print(sys.calls()); print(paste0(error)); respiroGui_push_error(paste0(error))}\n)"
			;

	setRunning(true);
	runRCommand(initRespiroR); 
	setRunning(false);
}

void RWrapper::volumeTestRespiro(int channel)
{	
	const QString scriptR =
			"withCallingHandlers(\n{\n"
			"  rc$channels[["+QString::number(channel)+"]]$volumeTest()\n"
			"\n},error=function(error) { print(sys.calls()); print(paste0(error)); respiroGui_push_error(paste0(error))}\n)"
			;

	setRunning(true);
	runRCommand(scriptR); 
	setRunning(false);
}

void RWrapper::leakTestRespiro(int channel)
{	
	const QString scriptR =
			"withCallingHandlers(\n{\n"
			"  rc$channels[["+QString::number(channel)+"]]$leakTest()\n"
			"\n},error=function(error) { print(sys.calls()); print(paste0(error)); respiroGui_push_error(paste0(error))}\n)"
			;

	setRunning(true);
	runRCommand(scriptR); 
	setRunning(false);
}

void RWrapper::startRespiro(int runtimeSec, int channelRuntimeSec, bool calibrateCO2, bool internalLeakTest, bool initialHsFlush)
{
	std::cout << "Starting respiro with runtimeSec=" << runtimeSec <<", channelRuntimeSec=" << channelRuntimeSec << ", calibrateCO2=" << (calibrateCO2 ? "yes":"no") <<
				 ", internalLeakTest="<< (internalLeakTest ? "yes":"no") << ", initialHsFlush="<< (initialHsFlush ? "yes":"no") << std::endl;
	std::cout << "Outputfolder: '" << _outputFolder.toStdString() << std::endl;

	(*R)[".runtimeSec"]			= runtimeSec;
	(*R)[".channelRuntimeSec"]	= channelRuntimeSec;
	(*R)[".calibrateCO2"]		= calibrateCO2;
	(*R)[".internalLeakTest"]	= internalLeakTest;
	(*R)[".initialHsFlush"]		= initialHsFlush;


	const QString startR =
			"withCallingHandlers(\n{\n"
			"  rc$start(\n"
			"    channels             = .channels,\n"
			"    monitorRunTime       = .runtimeSec,\n"
			"    calibrateCO2         = .calibrateCO2,\n"
			"    internalLeakTest     = .internalLeakTest,\n"
			"    monitorCycleDuration = .channelRuntimeSec,\n"
			"    initialHsFlush       = .initialHsFlush\n)"
			"\n},error=function(error) { print(sys.calls()); print(paste0(error)); respiroGui_push_error(paste0(error))}\n)"
			;

	setRunning(true);
	runRCommand(startR); //This will probably take a while ;)
	setRunning(false);
	runRCommand("rc$basalState(0)");
}

//From a direct connection so running in different thread than RWrapper itself!
void RWrapper::exitR()
{
	setControlWanted(true);

	int attempts = 20;

	while(_running && attempts-- > 0)
		QThread::msleep(200);

	if(_running)
	{
		std::cerr << "Couldnt exit R cleanly by asking control..." << std::endl;
		exit(2);
	}
	else
		std::cout << "R exited cleanly" <<std::endl;
}

QString RWrapper::getStringFromChannelConf(int channelID, const QString & confName)
{
	return QString::fromStdString(R->parseEvalNT("rc$channelConf(col='"+confName.toStdString()+"', channelID="+std::to_string(channelID)+")"));
}

void RWrapper::setStringIntoChannelConf(int channelID, const QString &confName, const QString &setting)
{
	R->parseEvalQNT("rc$channelConf(col='"+confName.toStdString()+"', newValue='"+setting.toStdString()+"', channelID="+std::to_string(channelID)+")");
}

double RWrapper::getDoubleFromChannelConf(int channelID, const QString &confName)
{
	return R->parseEvalNT("rc$channelConf(col='"+confName.toStdString()+"', channelID="+std::to_string(channelID)+")");
}

void RWrapper::setDoubleIntoChannelConf(int channelID, const QString &confName, const double setting)
{
	R->parseEvalQNT("rc$channelConf(col='"+confName.toStdString()+"', newValue="+std::to_string(setting)+", channelID="+std::to_string(channelID)+")");
}

bool RWrapper::running() const
{
	return _running;
}

void RWrapper::setRunning(bool newRunning)
{
	if (_running == newRunning)
		return;
	_running = newRunning;
	emit runningChanged();
}

QString RWrapper::outputFolder() const
{
	return _outputFolder;
}

void RWrapper::setOutputFolder(const QString & newOutputFolder)
{
	if (_outputFolder == newOutputFolder)
		return;
	_outputFolder = newOutputFolder;
	emit outputFolderChanged();
}

void respiroGui_push_status(std::string status)
{
	RWrapper::singleton()->setStatus(QString::fromStdString(status));
}

void respiroGui_push_plot(std::string plotJson, std::string plotType)
{
	RWrapper::singleton()->plotUpdated(plotJson, plotType);
}

void RWrapper::plotUpdated(const std::string & plotJson, const std::string & plotType)
{
	if(_plots.contains(plotType) && _plots.at(plotType) == plotJson) //Then we need to do nothing
		return;

	std::cerr << "Plot updated: " << plotType << /*": json: " << plotJson << */ std::endl;
	
	_plots[plotType] = plotJson;
	
	emit plotChanged(QString::fromStdString(plotType));
	
	if(		plotType == "allchan")			emit allChanPlotChanged(QString::fromStdString(plotJson));
	else if(plotType == "groupchan")		emit groupChanPlotChanged(QString::fromStdString(plotJson));
	else if(plotType == "meastimeline")		emit measTimePlotChanged(QString::fromStdString(plotJson));
    else if(plotType == "channel_status")	emit channelStatusChanged(QString::fromStdString(plotJson));


}

QString RWrapper::waitForPortChoice(QStringList ports)
{
	emit choosePort(ports);
	
	while(true)
	{
		_portMutex.lock();
		QString p = _chosenPort;
		_portMutex.unlock();
		
		if(p != "")
			return p;
		
		QThread::sleep(200);
	}
}

QString RWrapper::status() const
{
	return _status;
}

void RWrapper::setStatus(const QString &newStatus)
{
	if (_status == newStatus)
		return;
	
	std::cerr << "Status updated: " << newStatus.toStdString() << std::endl; 

	_status = newStatus;
	emit statusChanged();
}

QString RWrapper::allChanPlot() const
{
	return QString::fromStdString(_plots.at("allchan"));
}


QString RWrapper::groupChanPlot() const
{
	return QString::fromStdString(_plots.at("groupchan"));
}


QString RWrapper::measTimePlot() const
{
	return QString::fromStdString(_plots.at("meastimeline"));
}

QString RWrapper::channelStatus() const
{
	return QString::fromStdString(_plots.at("channel_status"));
}

QString RWrapper::chosenPort() const
{
	return _chosenPort;
}

void RWrapper::setChosenPort(const QString &newChosenPort)
{
	_portMutex.lock();
	
	if (_chosenPort == newChosenPort)
		return;
	
	_chosenPort = newChosenPort;
	_portMutex.unlock();
	
	emit chosenPortChanged();
}
