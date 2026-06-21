#include "respiro.h"
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <QUrl>
#include "database.h"
#include <iostream>
#include "rwrapper.h"
#include <QTimer>
#include <QMetaType>

Respiro::Respiro()
	: QAbstractListModel{}
{	
	//Create table, with columnsdefs:
	typedef ColumnDefinition	CD;

	_dataMeasuredDefs = {
		new CD("DB ID",					"id",				ColumnType::PrimaryKey),
		new CD("Timestamp",				"DateTime",			ColumnType::DateTime),
		new CD("Cycle",					"cycle",			ColumnType::NumInt),
		new CD("Phase",					"phase",			ColumnType::Text),
		new CD("Channel ID",			"channelID",		ColumnType::NumInt),
		new CD("Flow ml min",			"flow_ml_min",		ColumnType::NumDbl),
		new CD("O<sub>2</sub>%",		"O2_perc",			ColumnType::NumDbl),
		new CD("CH<sub>4</sub> ppm",	"CH4_ppm",			ColumnType::NumDbl),
		new CD("CO<sub>2</sub> ppm",	"CO2_ppm",			ColumnType::NumDbl),
		new CD("Pressure mBar",			"p_mBar",			ColumnType::NumDbl),
		new CD("Temperature",			"temp_C",			ColumnType::NumDbl),
		new CD("Sample temperature",	"sampleTemp_C",		ColumnType::NumDbl),
		new CD("Internal Vol. ml",		"intVol_ml",		ColumnType::NumDbl),
		new CD("hsVol ml",				"hsVol_ml",			ColumnType::NumDbl)
	};

	_dataProcessedDefs = {
		new CD("DB ID",					"id",				ColumnType::PrimaryKey),
		new CD("Cycle",					"cycle",			ColumnType::NumInt),
		new CD("Channel ID",			"channelID",		ColumnType::NumInt),
		new CD("Time from",				"DateTimeFrom",		ColumnType::DateTime),
		new CD("Time to",				"DateTimeTo",		ColumnType::DateTime),
		new CD("O<sub>2</sub> prod.",	"O2_umol_h",		ColumnType::NumDbl),
		new CD("CH<sub>4</sub> prod.",	"CH4_umol_h",		ColumnType::NumDbl),
		new CD("CO<sub>2</sub> prod.",	"CO2_umol_h",		ColumnType::NumDbl),
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
	_db			= new Database(dbPath().toStdString());
	_dataMeas	= new TableModel(	_db, "measurements",			_dataMeasuredDefs);
	_dataProc	= new TableModel(	_db, "prod",					_dataProcessedDefs);
	//_msgs		= new TableModel(	_db, "RespiroMsgs",				_msgsDefs);

	emit modelsLoaded();

    connect(RWrapper::singleton(), &RWrapper::allChanPlotChanged,	this, &Respiro::setAllChanPlot     , Qt::BlockingQueuedConnection );
    connect(RWrapper::singleton(), &RWrapper::measTimePlotChanged,	this, &Respiro::setMeasTimePlot    , Qt::BlockingQueuedConnection );
    connect(RWrapper::singleton(), &RWrapper::groupChanPlotChanged,	this, &Respiro::setGroupChanPlot   , Qt::BlockingQueuedConnection );
    connect(RWrapper::singleton(), &RWrapper::channelStatusChanged,	this, &Respiro::setChannelStatus   , Qt::BlockingQueuedConnection );
}

void Respiro::initSession()
{
	
	QDir	userOutputFolder	= _outputFolder;
	bool	outputOverride		= _outputFolder != "";
	
	if(!outputOverride)
	{
		QDir	newOutputDirParent	= QStandardPaths::standardLocations(QStandardPaths::AppDataLocation).at(0);
		QString	newFolder			= QDateTime::currentDateTimeUtc().toString("yyyy.MM.dd_hhmm");

		newOutputDirParent.mkpath(newFolder);

		setOutputFolder(QDir(newOutputDirParent.filePath(newFolder)).absolutePath());
	}
	else
	{
		if(!userOutputFolder.exists())
			userOutputFolder.mkpath(".");
	}


	init();

	//loadModels(); //Instead we will wait until respiro creates a database file!
}

void Respiro::startSession()
{
	initSession();

	startMeasuring();
}

void Respiro::continueSession()
{
	emit continueSignal();
}


void Respiro::loadOldSession(const QString & oldOutputdatafile)
{
	QFileInfo dataFileInfo(oldOutputdatafile.startsWith("file:") ? QUrl(oldOutputdatafile).toLocalFile() : oldOutputdatafile);
	
	std::cerr << "Trying to load old session from '" << dataFileInfo.absoluteFilePath().toStdString() << "'" << std::endl;
	
	if(!dataFileInfo.exists())
		emit cantFindOldDatabase();
	
	setOutputFolder(dataFileInfo.dir().absolutePath());
	_dataFilePath = dataFileInfo.absoluteFilePath();
	emit dbPathChanged();
	
	init();
}

bool Respiro::feedbackFinished(const QString & feedbackMsg)
{
	return _feedbackMap.contains(feedbackMsg) ? _feedbackMap[feedbackMsg]->finished : false;
}

QString Respiro::feedbackError(const QString & feedbackMsg)
{
	return _feedbackMap.contains(feedbackMsg) ? _feedbackMap[feedbackMsg]->error : "???";
}

int Respiro::rowCount(const QModelIndex &parent) const
{
	return _channels.size();
}

QVariant Respiro::data(const QModelIndex &index, int role) const
{
	if(index.row() < 0 || index.row() >= rowCount())
		return QVariant();
	
	switch(role) {
	case static_cast<int>(RespiroRole::channel):
		return QVariant::fromValue(_channels[index.row()]);
	case static_cast<int>(RespiroRole::channelID):
		return _channels[index.row()]->channelID();
	case static_cast<int>(RespiroRole::sampleID):
		return _channels[index.row()]->sampleID();
	case static_cast<int>(RespiroRole::hsVolMl):
		return _channels[index.row()]->hsVol_ml();
	case static_cast<int>(RespiroRole::co2MaxPpm):
		return _channels[index.row()]->CO2max_ppm();
	case static_cast<int>(RespiroRole::o2MinPerc):
		return _channels[index.row()]->O2min_perc();
	case static_cast<int>(RespiroRole::o2MaxPerc):
		return _channels[index.row()]->O2max_perc();
	case static_cast<int>(RespiroRole::ch4MaxPpm):
		return _channels[index.row()]->CH4max_ppm();
	case static_cast<int>(RespiroRole::leakPass):
		return _channels[index.row()]->leakPass();
	case static_cast<int>(RespiroRole::pressPass):
		return _channels[index.row()]->pressPass();
	case static_cast<int>(RespiroRole::volPass):
		return _channels[index.row()]->volPass();
	case static_cast<int>(RespiroRole::measureStable):
		return _channels[index.row()]->measureStable();
	case static_cast<int>(RespiroRole::isActive):
		return _channels[index.row()]->isActive();
	case static_cast<int>(RespiroRole::inExperiment):
		return _channels[index.row()]->inExperiment();
	case static_cast<int>(RespiroRole::cycle):
		return _channels[index.row()]->cycle();
	case static_cast<int>(RespiroRole::startTime):
		return _channels[index.row()]->startTime();
	case static_cast<int>(RespiroRole::completeCycle):
		return _channels[index.row()]->completeCycle();
	case static_cast<int>(RespiroRole::statusText):
		return _channels[index.row()]->statusText();
	case static_cast<int>(RespiroRole::statusColor):
		return _channels[index.row()]->color();
	default:
		return _channelConfs[index.row()]->channelID();
	}
}

QHash<int, QByteArray> Respiro::roleNames() const
{
	static QHash<int, QByteArray> rollen = [&]()
	{
		QHash<int, QByteArray> rollen = QAbstractListModel::roleNames();
		
		const auto roleMap = RespiroRoleToStringMap();
	for(const auto &pair : roleMap) {
		rollen[pair.first] = QByteArray(pair.second.c_str());
	}
		
		return rollen;
	}();
	return rollen;
}

const QString  Respiro::dbPath() const
{
	assert(_dataFilePath != "");
	return QFileInfo(_dataFilePath).absoluteFilePath();
}

float Respiro::O2() const
{
	return _O2;
}

void Respiro::setO2(float newO2)
{
	if (_O2 == newO2)
		return;
	_O2 = newO2;
	emit O2Changed();
}

float Respiro::CH4() const
{
	return _CH4;
}

void Respiro::setCh4(float newCh4)
{
	if (_CH4 == newCh4)
		return;
	_CH4 = newCh4;
	emit CH4Changed();
}

float Respiro::CO2() const
{
	return _CO2;
}

void Respiro::setCO2(float newCO2)
{
	if (_CO2 == newCO2)
		return;
	_CO2 = newCO2;
	emit CO2Changed();
}

float Respiro::pressure() const
{
	return _pressure;
}

void Respiro::setPressure(float newPressure)
{
	if (_pressure == newPressure)
		return;
	_pressure = newPressure;
	emit pressureChanged();
}

float Respiro::tempRespiro() const
{
	return _temp1;
}

void Respiro::seTemperatureRespirometer(float newTemp1)
{
	if (qFuzzyCompare(_temp1, newTemp1))
		return;
	_temp1 = newTemp1;
	emit temp1Changed();
}

float Respiro::tempSample() const
{
	return _temp2;
}

void Respiro::setTemperatureSample(float newTemp2)
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
	
	if (_controlWanted && !_running)
	{
		sendPumpOn(newPumpOn);
	}
	
	_pumpOn = newPumpOn;
	emit pumpOnChanged();
}

bool Respiro::O2On() const
{
	return _O2On;
}

void Respiro::setO2On(bool newO2On)
{
	if (_O2On == newO2On)
		return;
	_O2On = newO2On;
	emit O2OnChanged();
}

bool Respiro::CO2On() const
{
	return _CO2On;
}

void Respiro::setCO2On(bool newCO2On)
{
	if (_CO2On == newCO2On)
		return;
	_CO2On = newCO2On;
	emit CO2OnChanged();
}

bool Respiro::CH4On() const
{
	return _CH4On;
}

void Respiro::setCh4On(bool newCh4On)
{
	if (_CH4On == newCh4On)
		return;
	_CH4On = newCh4On;
	emit CH4OnChanged();
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
	
	std::cerr << "setControlWanted(" << (newControlWanted ? "True" : "False") << std::endl;
	
	_controlWanted = newControlWanted;
	emit controlWantedChanged(_controlWanted);
}

void Respiro::push_meas_data()
{
	QTimer::singleShot(2000, [&](){ dataMeas()->refresh(); });
}

void Respiro::push_proc_data()
{
	QTimer::singleShot(2000, [&](){ dataProc()->refresh(); });
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

void Respiro::push_vent_state(int vent, bool vent_open)
{
	switch(vent)
	{
	default:
	case 0:
		setVent0(vent_open);
		break;

	case 1:
		setVent1(vent_open);
		break;

	case 2:
		setVent2(vent_open);
		break;
	}
}

void Respiro::push_pump_state(bool pump_on)
{
	setPumpOn(pump_on);
}

void Respiro::push_O2_state(bool O2_on)
{
	setO2(O2_on);
}

void Respiro::push_CO2_state(bool CO2_on)
{
	setCO2(CO2_on);
}

void Respiro::push_CH4_state(bool CH4_on)
{
	setCh4(CH4_on);
}


void Respiro::push_generic_info(QString info, QString infoType)
{		
	if(_backlog.size() > 200)
		_backlog.erase(_backlog.begin(), _backlog.begin() + 100);
	
	
	_backlog << infoType + ": " + QString(10 - infoType.size(), ' ') + info;
	emit backlogChanged();
	
	

}


void Respiro::push_error(QString error)
{	
	std::cerr << error.toStdString() << std::endl;
	push_generic_info(error, "Error");
	
	//if(_msgs)
	//{
	//	if(_backlogError.size())
	//	{
	//		for(QString & m : _backlogError)
	//			_msgs->appendRows({{"Error", m, 0}});
	//		_backlogError.clear();
	//		emit backlogErrorChanged();
	//	}
	//	
	//	_msgs->appendRows({{"Error", error, QDateTime::currentSecsSinceEpoch()}}, &_msgsDefs);
	//}
	//else
	//{
	//	_backlogError << error;
	//	emit backlogErrorChanged();
	//}
	
}

void Respiro::push_warning(QString warning)
{	
	std::cout << warning.toStdString() << std::endl;
	push_generic_info(warning, "Warning");
	//if(_msgs)
	//{
	//	if(_backlogWarn.size())
	//	{
	//		for(QString & m : _backlogWarn)
	//			_msgs->appendRows({{"Warning", m, 0}});
	//		_backlogWarn.clear();
	//		emit backlogWarnChanged();
	//	}
	//	
	//	_msgs->appendRows({{"Warning", warning, QDateTime::currentSecsSinceEpoch()}}, &_msgsDefs);
	//}
	//else
	//{
	//	_backlogWarn << warning;	
	//	emit backlogWarnChanged();
	//}
}

void Respiro::push_info(QString info)
{
	push_generic_info(info, "Info");
	//if(_msgs)
	//{
	//	if(_backlogInfo.size())
	//	{
	//		for(QString & m : _backlogInfo)
	//			_msgs->appendRows({{"Info", m, 0}});
	//		_backlogInfo.clear();
	//		emit backlogInfoChanged();
	//	}
	//	
	//	_msgs->appendRows({{"Info", info, QDateTime::currentSecsSinceEpoch()}}, &_msgsDefs);
	//}
	//else
	//{
	//	_backlogInfo << info;
	//	emit backlogInfoChanged();
	//}
}

void Respiro::push_datafilepath(QString path)
{
	_dataFilePath = path;
	emit dbPathChanged();
	
	loadModels();
	
	if(_msgs)
		_msgs->appendRows({{"Info", "Datafile is at '" + _dataFilePath + "'", QDateTime::currentSecsSinceEpoch()}}, &_msgsDefs);
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

	if(feedback == "Initialising respirometer")
	{
		bool allSucces = true;

		for(Feedback * fb : _feedbacks)
			if(!fb->finished || !fb->error.isEmpty())
				allSucces = false;

		if(allSucces)
			emit respiroInited();
	}
}

void Respiro::init()
{
	beginResetModel();
	auto channelInts = initChannelsInts();
	emit initSignal(_dataFilePath, channelInts); //Init in R!
	
	for(int i : channelInts) {
		_channelConfs.push_back(new ChannelConf(i, RWrapper::singleton(), this));
		_channels.push_back(new Channel(i, this));
	}
	
	emit channelConfsChanged();
	endResetModel();
}

void Respiro::startMeasuring()
{
	emit startSignal(_runtimeTotalSec, _channelRuntimeSec);//, _calibrateCO2, _internalLeakTest, _initialHsFlush);
}

void Respiro::leakTests()
{
	emit leakTestsSignal();
}

void Respiro::leakTest(int c)
{
	emit leakTestSignal(c);
}

void Respiro::measure(int c)
{
	emit measureSignal(c);
}

void Respiro::flush(int c)
{
	emit flushSignal(c);
}

void Respiro::openedLid(int c)
{
	emit openedLidSignal(c);
}

void Respiro::measureHeadspacePost(int c)
{
	emit measureHeadspacePostSignal(c);
}

void Respiro::sendPumpOn(bool on)
{
	emit pumpOnSignal(on);
}

void Respiro::sendVent0(bool open)
{
	emit vent0Signal(open);
}

void Respiro::sendVent1(bool open)
{
	emit vent1Signal(open);
}

void Respiro::sendVent2(bool open)
{
	emit vent2Signal(open);
}

void Respiro::sendPumpBypass(bool bypass)
{
	emit pumpBypassSignal(bypass);
}

void Respiro::initialTests()
{
	emit showLoading();
	emit initTestsSignal(_calibrateCO2, _internalLeakTest, _initialHsFlush);
}

void Respiro::receive_last_values(int relTime, int measuring_channel, float pressure, float flow, float temperatureRespirometer, float temperatureSample, float CO2_ADC, float O2_raw, float CH4_raw, float CO2_raw)
{
	seTemperatureRespirometer(	temperatureRespirometer		);
	setTemperatureSample(		temperatureSample			);
	setRuntimeSec(				relTime						);
	setCurChannel(				measuring_channel			);
	setPressure(				pressure					);
	setCO2ADC(					CO2_ADC						);
	setFlow(					flow						);
	setCh4(						CH4_raw						);
	setCO2(						CO2_raw						);
	setO2(						O2_raw						);
}

const QString	&	 Respiro::outputFolder() const
{
	return _outputFolder;
}

void Respiro::setOutputFolder(const QString & newOutputFolder)
{
	if (_outputFolder == newOutputFolder)
		return;
	
	//std::cerr << "outputFolder changed to: " << newOutputFolder.toStdString() << std::endl;

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
	QList<int> l = {};

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

void Respiro::updateChannelConfig(int channelID, QString sampleID, double hsVol_ml,
								  double CO2max_ppm, double O2min_perc, double O2max_perc, double CH4max_ppm)
{
	for(Channel * c : _channels) {
		if(c->channelID() == channelID) {
			c->setSampleID(sampleID);
			c->setHsVol_ml(hsVol_ml);
			c->setCO2max_ppm(CO2max_ppm);
			c->setO2min_perc(O2min_perc);
			c->setO2max_perc(O2max_perc);
			c->setCH4max_ppm(CH4max_ppm);
			
			int row = static_cast<int>(std::distance(_channels.begin(), std::find_if(_channels.begin(), _channels.end(), [channelID](Channel* ch) { return ch->channelID() == channelID; })));
			QModelIndex topLeft = index(row, 0);
			QModelIndex bottomRight = index(row, 0);
			emit dataChanged(topLeft, bottomRight);
			break;
		}
	}
}

void Respiro::updateChannelStatus(int channelID, bool leakPass, bool pressPass, bool volPass, bool measureStable, bool isActive, bool inExperiment)
{
	for(Channel * c : _channels) {
		if(c->channelID() == channelID) {
			c->setLeakPass(leakPass);
			c->setPressPass(pressPass);
			c->setVolPass(volPass);
			c->setMeasureStable(measureStable);
			c->setActive(isActive);
			c->setInExperiment(inExperiment);
			
			int row = static_cast<int>(std::distance(_channels.begin(), std::find_if(_channels.begin(), _channels.end(), [channelID](Channel* ch) { return ch->channelID() == channelID; })));
			QModelIndex topLeft = index(row, 0);
			QModelIndex bottomRight = index(row, 0);
			emit dataChanged(topLeft, bottomRight);
			break;
		}
	}
}

void Respiro::updateChannelStatusText(int channelID, QString statusText)
{
	for(Channel * c : _channels) {
		if(c->channelID() == channelID) {
			c->setStatusText(statusText);
			
			int row = static_cast<int>(std::distance(_channels.begin(), std::find_if(_channels.begin(), _channels.end(), [channelID](Channel* ch) { return ch->channelID() == channelID; })));
			QModelIndex topLeft = index(row, 0);
			QModelIndex bottomRight = index(row, 0);
			emit dataChanged(topLeft, bottomRight);
			break;
		}
	}
}

void Respiro::updateChannelColor(int channelID, QString color)
{
	for(Channel * c : _channels) {
		if(c->channelID() == channelID) {
			c->setColor(color);
			
			int row = static_cast<int>(std::distance(_channels.begin(), std::find_if(_channels.begin(), _channels.end(), [channelID](Channel* ch) { return ch->channelID() == channelID; })));
			QModelIndex topLeft = index(row, 0);
			QModelIndex bottomRight = index(row, 0);
			emit dataChanged(topLeft, bottomRight);
			break;
		}
	}
}

void Respiro::updateChannelRuntime(int channelID, double cycle, double startTime, double completeCycle)
{
	for(Channel * c : _channels) {
		if(c->channelID() == channelID) {
			c->setCycle(cycle);
			c->setStartTime(startTime);
			c->setCompleteCycle(completeCycle);
			
			int row = static_cast<int>(std::distance(_channels.begin(), std::find_if(_channels.begin(), _channels.end(), [channelID](Channel* ch) { return ch->channelID() == channelID; })));
			QModelIndex topLeft = index(row, 0);
			QModelIndex bottomRight = index(row, 0);
			emit dataChanged(topLeft, bottomRight);
			break;
		}
	}
}

bool Respiro::vent0() const
{
	return _vent0;
}

void Respiro::setVent0(bool newVent0)
{
	if (_vent0 == newVent0)
		return;
	
	if (_controlWanted && !_running)
	{
		sendVent0(newVent0);
	}
	
	_vent0 = newVent0;
	emit vent0Changed();
}

bool Respiro::vent1() const
{
	return _vent1;
}

void Respiro::setVent1(bool newVent1)
{
	if (_vent1 == newVent1)
		return;
	
	if (_controlWanted && !_running)
	{
		sendVent1(newVent1);
	}
	
	_vent1 = newVent1;
	emit vent1Changed();
}

bool Respiro::vent2() const
{
	return _vent2;
}

void Respiro::setVent2(bool newVent2)
{
	if (_vent2 == newVent2)
		return;
	
	if (_controlWanted && !_running)
	{
		sendVent2(newVent2);
	}
	
	_vent2 = newVent2;
	emit vent2Changed();
}

QStringList __convertor(const QStringList & in)
{
	QStringList out = in.size() > 100 ? in.last(100) : in;
	
	std::reverse(out.begin(), out.end());
	
	return out;
}

QStringList Respiro::backlog() const
{
	return __convertor(_backlog);
}


QVariantList Respiro::channelConfs() const
{
	QVariantList out;
	
	for(ChannelConf * c : _channelConfs)
		out.append(QVariant::fromValue(c));
	
	return out;
}

QString Respiro::allChanPlot() const
{
    return _allChanPlot;
}

QString Respiro::measTimePlot() const
{
    return _measTimePlot;
}

QString Respiro::groupChanPlot() const
{
    return _groupChanPlot;
}

QString Respiro::channelStatus() const
{
    return _channelStatus;
}

void Respiro::setFlowChartLocalFile(const QString &newFlowChartFile)
{
	setFlowChartFile(QUrl::fromLocalFile(newFlowChartFile));
}

void Respiro::setAllChanPlot(const QString & newAllChanPlot)
{
	if (_allChanPlot == newAllChanPlot)
		return;
	_allChanPlot = newAllChanPlot;
	emit allChanPlotChanged();
}

void Respiro::setMeasTimePlot(const QString & newMeasTimePlot)
{
	if (_measTimePlot == newMeasTimePlot)
		return;
	
	_measTimePlot = newMeasTimePlot;
	emit measTimePlotChanged();
}

void Respiro::setGroupChanPlot(const QString & newGroupChanPlot)
{
	if (_groupChanPlot == newGroupChanPlot)
		return;
	
	_groupChanPlot = newGroupChanPlot;
	emit groupChanPlotChanged();
}

void Respiro::setChannelStatus(const QString & newChannelStatus)
{
	if (_channelStatus == newChannelStatus)
		return;

    std::cerr << "Channel status plot updated!" << std::endl; //is now: " << _channelStatus.toStdString() << std::endl;

	_channelStatus = newChannelStatus;
	emit channelStatusChanged();
}

QUrl Respiro::flowChartFile() const
{
	return _flowChartFile;
}

void Respiro::setFlowChartFile(const QUrl &newFlowChartFile)
{
	static int letsMakeThisVerySimple = 0;
	
	std::cerr << "Flowchart plot '" << newFlowChartFile.toString().toStdString() << "' updated!" << std::endl;
	
	_flowChartFile = newFlowChartFile;
	_flowChartFile.setQuery("?" + QString::number(letsMakeThisVerySimple++));
	
	emit flowChartFileChanged();
}

QString	Respiro::choosePort(QStringList )
{
	
	return _chosenPort;
}

QStringList Respiro::availablePorts() const
{
	return _availablePorts;
}

void Respiro::setAvailablePorts(const QStringList &newAvailablePorts)
{
	if (_availablePorts == newAvailablePorts)
		return;

	std::cerr<< "Respiro knows about available ports: " << newAvailablePorts.join(", ").toStdString() << std::endl;

	_availablePorts = newAvailablePorts;
	emit availablePortsChanged();
}

QString Respiro::chosenPort() const
{
	return _chosenPort;
}

void Respiro::setChosenPort(const QString &newChosenPort)
{
	std::cerr<< "setChosenPort " << newChosenPort.toStdString() << std::endl;
	if (_chosenPort == newChosenPort)
		return;
	_chosenPort = newChosenPort;
	emit chosenPortChanged(_chosenPort);
}

bool Respiro::running() const
{
	return _running;
}

void Respiro::setRunning(bool newRunning)
{
	if (_running == newRunning)
		return;
	_running = newRunning;
	emit runningChanged();
}

float Respiro::CO2ADC() const
{
	return _CO2ADC;
}

void Respiro::setCO2ADC(float newCO2ADC)
{
	if (qFuzzyCompare(_CO2ADC, newCO2ADC))
		return;
	_CO2ADC = newCO2ADC;
	emit CO2ADCChanged();
}

float Respiro::flow() const
{
	return _flow;
}

void Respiro::setFlow(float newFlow)
{
	if (qFuzzyCompare(_flow, newFlow))
		return;
	_flow = newFlow;
	emit flowChanged();
}

bool Respiro::pumpBypass() const
{
	return _pumpBypass;
}

void Respiro::setPumpBypass(bool newPumpBypass)
{
	if (_pumpBypass == newPumpBypass)
		return;
	
	if (_controlWanted && !_running)
	{
		sendPumpBypass(newPumpBypass);
	}
	
	_pumpBypass = newPumpBypass;
	emit pumpBypassChanged();
}

int Respiro::runtimeTotalSec() const
{
	return _runtimeTotalSec;
}

void Respiro::setRuntimeTotalSec(int newRuntimeTotalSec)
{
	if (_runtimeTotalSec == newRuntimeTotalSec)
		return;
	_runtimeTotalSec = newRuntimeTotalSec;
	emit runtimeTotalSecChanged();
}
