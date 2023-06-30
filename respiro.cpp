#include "respiro.h"
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QUrl>
#include "database.h"
#include <iostream>

Respiro::Respiro()
	: QObject{}
{	
	//Create table, with columnsdefs:
	typedef ColumnDefinition	CD;

	_dataDefs = {
		new CD("O<sub>2</sub>",		"o2",		ColumnType::NumInt),
		new CD("CH<sub>4</sub>",	"ch4",		ColumnType::NumInt),
		new CD("CO<sub>2</sub>",	"co2",		ColumnType::NumInt),
		new CD("Pressure",			"pressure",	ColumnType::NumInt),
		new CD("Temp. 1",			"temp1",	ColumnType::NumDbl),
		new CD("Temp. 2",			"temp2",	ColumnType::NumDbl),
		new CD("Timestamp",			"utc",		ColumnType::DateTime)
	};

	_msgsDefs =
	{
		new CD("Type",				"type",		ColumnType::Text),
		new CD("Message",			"msg",		ColumnType::Text),
		new CD("Timestamp",			"utc",		ColumnType::DateTime)
	};
}

void Respiro::loadModels()
{
	_db		= new Database(dbPath().toStdString());
	_labels	= new Labels(		_db, this);
	_data	= new TableModel(	_db, "RespiroData",	_dataDefs);
	_msgs	= new TableModel(	_db, "RespiroMsgs",	_msgsDefs);

	emit modelsLoaded();
}


void Respiro::startSession()
{
	QDir	newOutputFolder = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0);
	QString	newFolder		= QDateTime::currentDateTimeUtc().toString("yyyy.MM.dd_hhmm");

	newOutputFolder.mkpath(newFolder);

	setOutputFolder(QDir(newOutputFolder.filePath(newFolder)).absolutePath());


	loadModels();
	start();
}


void Respiro::loadOldSession(const QString & oldOutputFolder)
{
	setOutputFolder(oldOutputFolder);

	if(!QFileInfo::exists(dbPath()))
		emit cantFindOldDatabase();
	else
		loadModels();
}

bool Respiro::feedbackFinished(const QString & feedbackMsg)
{
	return _feedbackMap.contains(feedbackMsg) ? _feedbackMap[feedbackMsg]->finished : false;
}

QString Respiro::feedbackError(const QString & feedbackMsg)
{
	return _feedbackMap.contains(feedbackMsg) ? _feedbackMap[feedbackMsg]->error : "???";
}

const QString & Respiro::dbPath() const
{
	static QString dbPath;
	dbPath = QDir(_outputFolder).absoluteFilePath("respiro.sqlite");
	return dbPath;
}



int Respiro::o2() const
{
	return _o2;
}

void Respiro::setO2(int newO2)
{
	if (_o2 == newO2)
		return;
	_o2 = newO2;
	emit o2Changed();
}

int Respiro::ch4() const
{
	return _ch4;
}

void Respiro::setCh4(int newCh4)
{
	if (_ch4 == newCh4)
		return;
	_ch4 = newCh4;
	emit ch4Changed();
}

int Respiro::co2() const
{
	return _co2;
}

void Respiro::setCo2(int newCo2)
{
	if (_co2 == newCo2)
		return;
	_co2 = newCo2;
	emit co2Changed();
}

int Respiro::pressure() const
{
	return _pressure;
}

void Respiro::setPressure(int newPressure)
{
	if (_pressure == newPressure)
		return;
	_pressure = newPressure;
	emit pressureChanged();
}

float Respiro::temp1() const
{
	return _temp1;
}

void Respiro::setTemp1(float newTemp1)
{
	if (qFuzzyCompare(_temp1, newTemp1))
		return;
	_temp1 = newTemp1;
	emit temp1Changed();
}

float Respiro::temp2() const
{
	return _temp2;
}

void Respiro::settemp2(float newTemp2)
{
	if (qFuzzyCompare(_temp2, newTemp2))
		return;
	_temp2 = newTemp2;
	emit temp2Changed();
}

const QString	&	 Respiro::error() const
{
	return _error;
}

void Respiro::setError(const QString & newError)
{
	if (_error == newError)
		return;
	_error = newError;
	emit errorChanged();
}

const QString	&	 Respiro::warning() const
{
	return _warning;
}

void Respiro::setWarning(const QString & newWarning)
{
	if (_warning == newWarning)
		return;
	_warning = newWarning;
	emit warningChanged();
}

int Respiro::curChannel() const
{
	return _curChannel;
}

void Respiro::setCurChannel(int newCurChannel)
{
	if (_curChannel == newCurChannel)
		return;
	_curChannel = newCurChannel;
	emit curChannelChanged();
}

QVariantList Respiro::valvesOpened() const
{
	QVariantList l;
	for(size_t i=0; i<std::max(size_t(13), _valvesOpened.size()); i++)
		l.push_back(_valvesOpened.size()>i ? _valvesOpened[i] : false);
	return l;
}

bool Respiro::pumpOn() const
{
	return _pumpOn;
}

void Respiro::setPumpOn(bool newPumpOn)
{
	if (_pumpOn == newPumpOn)
		return;
	_pumpOn = newPumpOn;
	emit pumpOnChanged();
}

bool Respiro::o2On() const
{
	return _o2On;
}

void Respiro::setO2On(bool newO2On)
{
	if (_o2On == newO2On)
		return;
	_o2On = newO2On;
	emit o2OnChanged();
}

bool Respiro::co2On() const
{
	return _co2On;
}

void Respiro::setCo2On(bool newCo2On)
{
	if (_co2On == newCo2On)
		return;
	_co2On = newCo2On;
	emit co2OnChanged();
}

bool Respiro::ch4On() const
{
	return _ch4On;
}

void Respiro::setCh4On(bool newCh4On)
{
	if (_ch4On == newCh4On)
		return;
	_ch4On = newCh4On;
	emit ch4OnChanged();
}

bool Respiro::instantPause() const
{
	return _instantPause;
}

void Respiro::setInstantPause(bool newInstantPause)
{
	if (_instantPause == newInstantPause)
		return;
	_instantPause = newInstantPause;
	emit instantPauseChanged(_instantPause);
}

bool Respiro::delayedPause() const
{
	return _delayedPause;
}

void Respiro::setDelayedPause(bool newDelayedPause)
{
	if (_delayedPause == newDelayedPause)
		return;
	_delayedPause = newDelayedPause;
	emit delayedPauseChanged(_delayedPause);
}

bool Respiro::controlWanted() const
{
	return _controlWanted;
}

void Respiro::setControlWanted(bool newControlWanted)
{
	if (_controlWanted == newControlWanted)
		return;
	_controlWanted = newControlWanted;
	emit controlWantedChanged(_controlWanted);
}

void Respiro::push_raw_data(int o2, int ch4, int co2, int pressure, float temp1, float temp2)
{
	data()->appendRows({{o2, ch4, co2, pressure, temp1, temp2, QDateTime::currentDateTimeUtc().toSecsSinceEpoch()}}, &_dataDefs);
}

void Respiro::push_current_channel(int channel)
{
	setCurChannel(channel);
}

void Respiro::push_valve_state(int channel, bool valve_open)
{
	bool changed = false;
	if(channel >= _valvesOpened.size())
		_valvesOpened.resize(channel + 1);

	changed = _valvesOpened[channel] != valve_open;
	_valvesOpened[channel] = valve_open;

	if(changed)
		emit valvesOpenedChanged();
}

void Respiro::push_pump_state(bool pump_on)
{
	setPumpOn(pump_on);
}

void Respiro::push_o2_state(bool o2_on)
{
	setO2(o2_on);
}

void Respiro::push_co2_state(bool co2_on)
{
	setCo2(co2_on);
}

void Respiro::push_ch4_state(bool ch4_on)
{
	setCh4(ch4_on);
}

void Respiro::push_error(QString error)
{
	std::cerr << error.toStdString() << std::endl;
	_msgs->appendRows({{"Error", error, QDateTime::currentDateTimeUtc().toSecsSinceEpoch()}}, &_msgsDefs);
}

void Respiro::push_warning(QString warning)
{
	std::cout << warning.toStdString() << std::endl;
	_msgs->appendRows({{"Warning", warning, QDateTime::currentDateTimeUtc().toSecsSinceEpoch()}}, &_msgsDefs);
}

void Respiro::push_info(QString info)
{
	_msgs->appendRows({{"Info", info, QDateTime::currentDateTimeUtc().toSecsSinceEpoch()}}, &_msgsDefs);
}

void Respiro::push_loading_feedback(QString feedback, bool finished, QString error)
{
	std::cout << "push_loading_feedback('" << feedback.toStdString() << "', '" << (finished ? "finished" : "not finished") << "', '" << error.toStdString() << "')" << std::endl;

	if(_feedbackMap.contains(feedback))
	{
		_feedbackMap[feedback]->error		= error;
		_feedbackMap[feedback]->finished	= finished;
	}
	else
	{
		Feedback * fb = new Feedback(feedback, finished, error);
		_feedbacks.push_back(fb);
		_feedbackMap[feedback] = fb;
	}
	_hardResetFeedback = true;
	emit feedbackChanged();
	_hardResetFeedback = false;
	emit feedbackChanged();
}

void Respiro::start()
{
	emit startSignal(initChannelsInts(), _runtimeSec, _channelRuntimeSec, _calibrateCO2, _internalLeakTest, _initialHsFlush);
}

const QString	&	 Respiro::outputFolder() const
{
	return _outputFolder;
}

void Respiro::setOutputFolder(const QString & newOutputFolder)
{
	if (_outputFolder == newOutputFolder)
		return;

	_outputFolder = newOutputFolder.startsWith("file:") ? QUrl(newOutputFolder).toLocalFile() : newOutputFolder;
	emit outputFolderChanged(_outputFolder);
}

QStringList Respiro::feedback() const
{
	QStringList fbs;
	if(!_hardResetFeedback)
		for(Feedback * fb : _feedbacks)
			fbs.append(fb->feedback);
	return fbs;
}

QVariantList Respiro::channelInit() const
{
	return _channelInit;
}

QList<int> Respiro::initChannelsInts() const
{
	QList<int> l;

	for(int i=0; i<_channelInit.size(); i++)
		if(_channelInit[i].toBool())
			l.append(i);

	return l;
}

void Respiro::setChannelInit(const QVariantList & newChannelInit)
{
	if (_channelInit == newChannelInit)
		return;

	_channelInit = newChannelInit;
	emit channelInitChanged();
}

void Respiro::setChannelInit(int index, bool checked)
{
	if(index >= _channelInit.size())
		_channelInit.resize(index+1);

	_channelInit[index] = checked;
	emit channelInitChanged();
}

int Respiro::channelRuntimeSec() const
{
	return _channelRuntimeSec;
}

void Respiro::setChannelRuntimeSec(int newChannelRuntimeSec)
{
	if (_channelRuntimeSec == newChannelRuntimeSec)
		return;
	_channelRuntimeSec = newChannelRuntimeSec;
	emit channelRuntimeSecChanged();
}

bool Respiro::calibrateCO2() const
{
	return _calibrateCO2;
}

void Respiro::setCalibrateCO2(bool newCalibrateCO2)
{
	if (_calibrateCO2 == newCalibrateCO2)
		return;
	_calibrateCO2 = newCalibrateCO2;
	emit calibrateCO2Changed();
}

bool Respiro::internalLeakTest() const
{
	return _internalLeakTest;
}

void Respiro::setInternalLeakTest(bool newInternalLeakTest)
{
	if (_internalLeakTest == newInternalLeakTest)
		return;
	_internalLeakTest = newInternalLeakTest;
	emit internalLeakTestChanged();
}

bool Respiro::initialHsFlush() const
{
	return _initialHsFlush;
}

void Respiro::setInitialHsFlush(bool newInitialHsFlush)
{
	if (_initialHsFlush == newInitialHsFlush)
		return;
	_initialHsFlush = newInitialHsFlush;
	emit initialHsFlushChanged();
}

int Respiro::runtimeSec() const
{
	return _runtimeSec;
}

void Respiro::setRuntimeSec(int newRuntimeSec)
{
	if (_runtimeSec == newRuntimeSec)
		return;
	_runtimeSec = newRuntimeSec;
	emit runtimeSecChanged();
}
