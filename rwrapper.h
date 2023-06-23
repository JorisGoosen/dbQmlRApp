#ifndef RWRAPPER_H
#define RWRAPPER_H

#include <QObject>
#include <RInside.h>

void respiroGui_push_raw_data(			int			o2, int ch4, int co2, int pressure, float temp1, float temp2);
void respiroGui_push_current_channel(	int			channel);
void respiroGui_push_valve_state(		int			channel, bool valve_open);
void respiroGui_push_pump_state(		bool		pump_on);
void respiroGui_push_o2_state(			bool		o2_on);
void respiroGui_push_co2_state(			bool		co2_on);
void respiroGui_push_ch4_state(			bool		ch4_on);
void respiroGui_push_error(				std::string	error);
void respiroGui_push_warning(			std::string	warning);
void respiroGui_push_info(				std::string	info);
bool respiroGui_poll_instant_pause();
bool respiroGui_poll_delayed_pause();
bool respiroGui_poll_control_wanted();
void respiroGui_push_loading_feedback(	std::string feedback, bool finished, std::string errorMsg);

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

public slots:
	void startRespiro(
			QList<int>	channels,
			int			runtimeSec,
			int			channelRuntimeSec,
			bool		calibrateCO2,
			bool		internalLeakTest,
			bool		initialHsFlush
	);

	void exitR();

signals:
	void prevOutputChanged();
	void plotWidthChanged(int w);
	void plotHeightChanged(int h);

	void push_raw_data(			int		o2, int ch4, int co2, int pressure, float temp1, float temp2);
	void push_current_channel(	int		channel);
	void push_valve_state(		int		channel, bool valve_open);
	void push_pump_state(		bool	pump_on);
	void push_o2_state(			bool	o2_on);
	void push_co2_state(		bool	co2_on);
	void push_ch4_state(		bool	ch4_on);
	void push_error(			QString	error);
	void push_warning(			QString	warning);
	void push_info(				QString	warning);
	void push_loading_feedback(	QString feedback, bool finished, QString error);


	void instantPauseChanged();
	void delayedPauseChanged();
	void controlWantedChanged();
	void runningChanged();


	void outputFolderChanged();

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
	QString _outputFolder;
};

#endif // RWRAPPER_H
