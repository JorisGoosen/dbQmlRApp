#ifndef RWRAPPER_H
#define RWRAPPER_H

#include <QMutex>
#include <QObject>
#include <RInside.h>

void		respiroGui_push_meas_data();
void		respiroGui_push_proc_data();
void		respiroGui_push_last_values( int relTime, int measuring_channel, float pressure, float flow, float temperatureRespirometer, float temperatureSample, float CO2_ADC, float O2_raw, float CH4_raw, float CO2_raw);
void		respiroGui_push_current_channel(	int			channel);
void		respiroGui_push_valve_state(		int			channel,	bool valve_open);
void		respiroGui_push_vent_state(		int			id,			bool vent_open);
void		respiroGui_push_pump_state(		bool		pump_on);
void		respiroGui_push_o2_state(			bool		o2_on);
void		respiroGui_push_co2_state(			bool		co2_on);
void		respiroGui_push_ch4_state(			bool		ch4_on);
void		respiroGui_push_error(				std::string	error);
void		respiroGui_push_warning(			std::string	warning);
void		respiroGui_push_info(				std::string	info);
void		respiroGui_push_status(			std::string	status);
void		respiroGui_push_plot(				std::string	plotJson, std::string plotType);
void		respiroGui_update_flow_diagram(	std::string png);
void		respiroGui_push_datafilepath(std::string datafile);
void		respiroGui_push_loading_feedback(	std::string feedback, bool finished, std::string errorMsg);
std::string respiroGui_ask_which_port(			Rcpp::CharacterVector);
bool		respiroGui_poll_instant_pause();
bool		respiroGui_poll_delayed_pause();
bool		respiroGui_poll_control_wanted();

typedef std::map<std::string,std::string> strMap;

class RWrapper : public QObject
{
  Q_OBJECT

	Q_PROPERTY(QStringList	prevOutput			READ prevOutput			WRITE setPrevOutput		NOTIFY prevOutputChanged	)
	Q_PROPERTY(QString		prevOutputConcat	READ prevOutputConcat							NOTIFY prevOutputChanged	)
	Q_PROPERTY(int			plotWidth			READ plotWidth			WRITE setPlotWidth		NOTIFY plotWidthChanged		)
	Q_PROPERTY(int			plotHeight			READ plotHeight			WRITE setPlotHeight		NOTIFY plotHeightChanged	)
	Q_PROPERTY(bool			instantPause		READ instantPause		WRITE setInstantPause	NOTIFY instantPauseChanged	)
	Q_PROPERTY(bool			delayedPause		READ delayedPause		WRITE setDelayedPause	NOTIFY delayedPauseChanged	)
	Q_PROPERTY(bool			controlWanted		READ controlWanted		WRITE setControlWanted	NOTIFY controlWantedChanged	)
	Q_PROPERTY(bool			running				READ running			WRITE setRunning		NOTIFY runningChanged		)
	Q_PROPERTY(QString		outputFolder		READ outputFolder		WRITE setOutputFolder	NOTIFY outputFolderChanged	)
	Q_PROPERTY(QString		status				READ status				WRITE setStatus			NOTIFY statusChanged		)
	Q_PROPERTY(QString		allChanPlot			READ allChanPlot								NOTIFY allChanPlotChanged	)
	Q_PROPERTY(QString		measTimePlot		READ measTimePlot								NOTIFY measTimePlotChanged	)
	Q_PROPERTY(QString		groupChanPlot		READ groupChanPlot								NOTIFY groupChanPlotChanged	)
	Q_PROPERTY(QString		channelStatus		READ channelStatus								NOTIFY channelStatusChanged	)
	Q_PROPERTY(QString  	chosenPort			READ chosenPort			WRITE setChosenPort					NOTIFY chosenPortChanged		)
	

public:
    explicit RWrapper(QObject *parent = nullptr);

	Q_INVOKABLE QString runRCommand(QString command);

	QStringList prevOutput()		const;
	QString		prevOutputConcat()	const { return prevOutput().join("\n"); }
	void		setPrevOutput(const QStringList & newPrevOutput);

	int plotWidth() const;
	int plotHeight() const;

	void setPlotWidth(int newPlotWidth);
	void setPlotHeight(int newPlotHeight);

	static RWrapper * singleton() { return _singleton; }

	bool instantPause() const;
	bool delayedPause() const;
	bool controlWanted() const;
	bool running() const;

	void setInstantPause(bool newInstantPause);
	void setDelayedPause(bool newDelayedPause);
	void setControlWanted(bool newControlWanted);
	void setRunning(bool newRunning);

	QString outputFolder() const;
	void setOutputFolder(const QString & newOutputFolder);

	
	QString status() const;
	void setStatus(const QString &newStatus);
	
	QString allChanPlot() const;
	
	QString measTimePlot() const;
	
	QString groupChanPlot() const;
	QString channelStatus() const;
	
	QString chosenPort() const;
	void setChosenPort(const QString &newChosenPort);
	
public slots:
	void initRespiro(
			QString		datafile,
			QList<int>	channels
	);
	
	void startRespiro(
			int			runtimeSec,
			int			channelRuntimeSec,
			bool		calibrateCO2,
			bool		internalLeakTest,
			bool		initialHsFlush
	);

	void volumeTestRespiro(int channel);
	void leakTestRespiro(int channel);

	void exitR();
	
	QString		getStringFromChannelConf(int channelID, const QString & confName);
	void		setStringIntoChannelConf(int channelID, const QString & confName, const QString & setting);
	
	double		getDoubleFromChannelConf(int channelID, const QString & confName);
	void		setDoubleIntoChannelConf(int channelID, const QString & confName, const double setting);
	
	void		plotUpdated(const std::string & plotJson, const std::string & plotType);
	QString		waitForPlotChoice(QStringList ports);

signals:	
	void prevOutputChanged();
	void plotWidthChanged(int w);
	void plotHeightChanged(int h);
	void push_last_values( int relTime, int measuring_channel, float pressure, float flow, float temperatureRespirometer, float temperatureSample, float CO2_ADC, float O2_raw, float CH4_raw, float CO2_raw);
	void push_meas_data();
	void push_proc_data();
	void push_current_channel(	int		channel);
	void push_valve_state(		int		channel, bool valve_open);
	void push_pump_state(		bool	pump_on);
	void push_O2_state(			bool	O2_on);
	void push_CO2_state(		bool	CO2_on);
	void push_CH4_state(		bool	CH4_on);
	void push_error(			QString	error);
	void push_warning(			QString	warning);
	void push_info(				QString	warning);
	void push_loading_feedback(	QString feedback, bool finished, QString error);
	void push_vent_state(		int		vent, bool valve_open);
	void push_datafilepath(		QString datafile);
	QString choosePort(			QStringList ports);

	void instantPauseChanged();
	void delayedPauseChanged();
	void controlWantedChanged();
	void runningChanged();
	void outputFolderChanged();
	void statusChanged();
	void plotChanged(QString);
	void allChanPlotChanged(QString allChanPlot);
	void measTimePlotChanged(QString measTimePlot);
	void groupChanPlotChanged(QString groupChanPlot);
	void channelStatusChanged(QString channelStatus);
	void flowChartPlotUpdated(QString fileName);

	void chosenPortChanged();
	
private:
	RInside			*	R				= nullptr;
	QStringList			_prevOutput		= { };
	int					_plotWidth		= 500,
						_plotHeight		= 300;
	static RWrapper	*	_singleton;
	bool				_instantPause	= false,
						_delayedPause	= false,
						_controlWanted	= false,
						_running		= false;
	QString				_outputFolder,
						_status,
						_chosenPort		= "";
	strMap				_plots;
	
	QMutex				_portMutex;
};

#endif // RWRAPPER_H
