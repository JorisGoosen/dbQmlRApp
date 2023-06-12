#include "rwrapper.h"

RWrapper * RWrapper::_singleton = nullptr;

RWrapper::RWrapper(QObject *parent)
	: QObject{parent}, R(new RInside(0, nullptr, true, false, false))
{
	assert(!_singleton);
	_singleton = this;

	(*R)["respiroGui_push_raw_data"]				= Rcpp::InternalFunction(&respiroGui_push_raw_data);
	(*R)["respiroGui_push_current_channel"]			= Rcpp::InternalFunction(&respiroGui_push_current_channel);
	(*R)["respiroGui_push_valve_state"]				= Rcpp::InternalFunction(&respiroGui_push_valve_state);
	(*R)["respiroGui_push_pump_state"]				= Rcpp::InternalFunction(&respiroGui_push_pump_state);
	(*R)["respiroGui_push_o2_state"]				= Rcpp::InternalFunction(&respiroGui_push_o2_state);
	(*R)["respiroGui_push_co2_state"]				= Rcpp::InternalFunction(&respiroGui_push_co2_state);
	(*R)["respiroGui_push_ch4_state"]				= Rcpp::InternalFunction(&respiroGui_push_ch4_state);
	(*R)["respiroGui_push_error"]					= Rcpp::InternalFunction(&respiroGui_push_error);
	(*R)["respiroGui_push_warning"]					= Rcpp::InternalFunction(&respiroGui_push_warning);
	(*R)["respiroGui_poll_instant_pause"]			= Rcpp::InternalFunction(&respiroGui_poll_instant_pause);
	(*R)["respiroGui_poll_delayed_pause"]			= Rcpp::InternalFunction(&respiroGui_poll_delayed_pause);
	(*R)["respiroGui_poll_control_wanted"]			= Rcpp::InternalFunction(&respiroGui_poll_control_wanted);
	(*R)["respiroGui_push_loading_feedback"]		= Rcpp::InternalFunction(&respiroGui_push_loading_feedback);

}

QString RWrapper::runRCommand(QString command)
{
	std::cout << "Running R command:\n" << command.toStdString() << std::endl;

	RInside::Proxy res = R->parseEvalNT(command.toStdString());

	std::function<QString(SEXP sexp)> f;

	f = [&](SEXP res)
	{
		QStringList out;

		if(Rf_isString(res))
			for(Rcpp::String str : Rcpp::StringVector(res))
				out.append(QString::fromStdString(str));
		else if(Rf_isInteger(res))
			for(int r : Rcpp::IntegerVector(res))
				out.append(QString::number(r));
		else if(Rf_isReal(res))
			for(double r : Rcpp::DoubleVector(res))
				out.append(QString::number(r));
		else if(Rf_isNull(res))
			out.append("NULL");
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

void respiroGui_push_raw_data(			int			o2, int ch4, int co2, int pressure, float temp1, float temp2)
{
	emit RWrapper::singleton()->push_raw_data(o2, ch4, co2, pressure, temp1, temp2);
}

void respiroGui_push_current_channel(	int			channel)
{
	emit RWrapper::singleton()->push_current_channel(channel);
}

void respiroGui_push_valve_state(		int			channel, bool valve_open)
{
	emit RWrapper::singleton()->push_valve_state(channel, valve_open);
}

void respiroGui_push_pump_state(		bool		pump_on)
{
	emit RWrapper::singleton()->push_pump_state(pump_on);
}

void respiroGui_push_o2_state(			bool		o2_on)
{
	emit RWrapper::singleton()->push_o2_state(o2_on);
}

void respiroGui_push_co2_state(			bool		co2_on)
{
	emit RWrapper::singleton()->push_co2_state(co2_on);
}

void respiroGui_push_ch4_state(			bool		ch4_on)
{
	emit RWrapper::singleton()->push_ch4_state(ch4_on);
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

void RWrapper::startRespiro(QList<int> channels, int runtimeSec, int channelRuntimeSec, bool calibrateCO2, bool internalLeakTest, bool initialHsFlush)
{
	(*R)[".runtimeSec"]			= runtimeSec;
	(*R)[".channelRuntimeSec"]	= channelRuntimeSec;
	(*R)[".calibrateCO2"]		= calibrateCO2;
	(*R)[".internalLeakTest"]	= internalLeakTest;
	(*R)[".initialHsFlush"]		= initialHsFlush;

	const QString startR =
			"library(respiro)\n"
			"channels = " + [channels](){ QStringList l; for(int channel : channels) l.append(QString::number(channel)); return ("c(" + l.join(",") + ")"); }() + "\n"
			"rc = RespiroControl$new(channels)\n"
			"rc$start(\n"
			"  runtime=.runtimeSec,\n"
			"  channelRuntime=.channelRuntimeSec,\n"
			"  CalibrateCO2=.calibrateCO2,\n"
			"  Internalleaktest=.internalLeakTest,\n"
			"  InitialHsFlush=.initialHsFlush\n)";

	setRunning(true);
	runRCommand(startR); //This will probably take a while ;)
	setRunning(false);
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
