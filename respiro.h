#ifndef RESPIRO_H
#define RESPIRO_H

#include "channelconf.h"
#include "tablemodel.h"
#include <QObject>
#include <QUrl>

struct Feedback
{
	QString feedback,
			error;
	bool	finished;

	Feedback(QString feedback, bool finished, QString error)
		:	feedback(feedback), error(error), finished(finished)
	{}
};

typedef std::vector<Feedback *>			Feedbacks;
typedef std::map<QString, Feedback*>	FeedbackMap;

class Respiro : public QObject
{
	Q_OBJECT
	Q_PROPERTY(float		O2					READ O2					WRITE setO2							NOTIFY O2Changed				)
	Q_PROPERTY(float		CH4					READ CH4				WRITE setCh4						NOTIFY CH4Changed				)
	Q_PROPERTY(float		CO2					READ CO2				WRITE setCO2						NOTIFY CO2Changed				)
	Q_PROPERTY(float		pressure			READ pressure			WRITE setPressure					NOTIFY pressureChanged			)
    Q_PROPERTY(float		tempRespiro			READ tempRespiro		WRITE seTemperatureRespirometer		NOTIFY temp1Changed				)
    Q_PROPERTY(float		tempSample			READ tempSample			WRITE setTemperatureSample			NOTIFY temp2Changed				)
	Q_PROPERTY(QString		error				READ error				WRITE setError						NOTIFY errorChanged				)
	Q_PROPERTY(QString		warning				READ warning			WRITE setWarning					NOTIFY warningChanged			)
	
	Q_PROPERTY(int			curChannel			READ curChannel			WRITE setCurChannel					NOTIFY curChannelChanged		)
	Q_PROPERTY(QVariantList valvesOpened		READ valvesOpened											NOTIFY valvesOpenedChanged		) //List of booleans
	Q_PROPERTY(bool			pumpOn				READ pumpOn				WRITE setPumpOn						NOTIFY pumpOnChanged			)
	Q_PROPERTY(bool			O2On				READ O2On				WRITE setO2On						NOTIFY O2OnChanged				)
	Q_PROPERTY(bool			CO2On				READ CO2On				WRITE setCO2On						NOTIFY CO2OnChanged				)
	Q_PROPERTY(bool			CH4On				READ CH4On				WRITE setCh4On						NOTIFY CH4OnChanged				)

	Q_PROPERTY(bool			vent0				READ vent0				WRITE setVent0						NOTIFY vent0Changed				)
	Q_PROPERTY(bool			vent1				READ vent1				WRITE setVent1						NOTIFY vent1Changed				)
	Q_PROPERTY(bool			vent2				READ vent2				WRITE setVent2						NOTIFY vent2Changed				)

	Q_PROPERTY(bool			instantPause		READ instantPause		WRITE setInstantPause				NOTIFY instantPauseChanged		)
	Q_PROPERTY(bool			delayedPause		READ delayedPause		WRITE setDelayedPause				NOTIFY delayedPauseChanged		)
	Q_PROPERTY(bool			controlWanted		READ controlWanted		WRITE setControlWanted				NOTIFY controlWantedChanged		)

	Q_PROPERTY(QString		outputFolder		READ outputFolder		WRITE setOutputFolder				NOTIFY outputFolderChanged		)
	Q_PROPERTY(QStringList	feedback			READ feedback												NOTIFY feedbackChanged			)

	Q_PROPERTY(QVariantList channelInit			READ channelInit		WRITE setChannelInit				NOTIFY channelInitChanged		) //List of booleans
	Q_PROPERTY(int			runtimeSec			READ runtimeSec			WRITE setRuntimeSec					NOTIFY runtimeSecChanged		)
	Q_PROPERTY(int			channelRuntimeSec	READ channelRuntimeSec	WRITE setChannelRuntimeSec			NOTIFY channelRuntimeSecChanged	)
	Q_PROPERTY(bool			calibrateCO2		READ calibrateCO2		WRITE setCalibrateCO2				NOTIFY calibrateCO2Changed		)
	Q_PROPERTY(bool			internalLeakTest	READ internalLeakTest	WRITE setInternalLeakTest			NOTIFY internalLeakTestChanged	)
	Q_PROPERTY(bool			initialHsFlush		READ initialHsFlush		WRITE setInitialHsFlush				NOTIFY initialHsFlushChanged	)
	
	Q_PROPERTY(QStringList	backlog				READ backlog												NOTIFY backlogChanged			)
	Q_PROPERTY(QVariantList	channelConfs		READ channelConfs											NOTIFY channelConfsChanged		)

    Q_PROPERTY(QString		allChanPlot			READ allChanPlot		WRITE setAllChanPlot				NOTIFY allChanPlotChanged	)
    Q_PROPERTY(QString		measTimePlot		READ measTimePlot		WRITE setMeasTimePlot				NOTIFY measTimePlotChanged	)
    Q_PROPERTY(QString		groupChanPlot		READ groupChanPlot		WRITE setGroupChanPlot				NOTIFY groupChanPlotChanged	)
    Q_PROPERTY(QString		channelStatus		READ channelStatus		WRITE setChannelStatus				NOTIFY channelStatusChanged	)
	Q_PROPERTY(QUrl			flowChartFile		READ flowChartFile		WRITE setFlowChartFile				NOTIFY flowChartFileChanged )

	Q_PROPERTY(QStringList	availablePorts		READ availablePorts		WRITE setAvailablePorts				NOTIFY availablePortsChanged 	)
	Q_PROPERTY(QString  	chosenPort			READ chosenPort			WRITE setChosenPort					NOTIFY chosenPortChanged		)

public:
	explicit Respiro();

	Q_INVOKABLE	void	startSession();
	Q_INVOKABLE	void	initSession();
	Q_INVOKABLE	void	loadOldSession(const QString & oldOutputFolder);

	Q_INVOKABLE	bool	feedbackFinished(	const QString & feedbackMsg);
	Q_INVOKABLE	QString	feedbackError(		const QString & feedbackMsg);


	Database	*		db()			const	{ return _db;		}
	TableModel	*		dataMeas()		const	{ return _dataMeas;	}
	TableModel	*		dataProc()		const	{ return _dataProc;	}
	TableModel	*		msgs()			const	{ return _msgs;		}

	float				O2()				const;
	float				CH4()				const;
	float				CO2()				const;
	float				pressure()			const;
	float				tempRespiro()				const;
	float				tempSample()				const;
	const QString	&	error()				const;
	const QString	&	warning()			const;
	int					curChannel()		const;
	QVariantList		valvesOpened()		const;
	bool				pumpOn()			const;
	bool				O2On()				const;
	bool				CO2On()				const;
	bool				CH4On()				const;
	bool				instantPause()		const;
	bool				delayedPause()		const;
	bool				controlWanted()		const;
	const QString	&	outputFolder()		const;
	const QString		dbPath()			const;
	QStringList			feedback()			const;
	QVariantList		channelInit()		const;
	QList<int>			initChannelsInts()	const;
	int					channelRuntimeSec() const;
	bool				calibrateCO2()		const;
	bool				internalLeakTest()	const;
	bool				initialHsFlush()	const;
	int					runtimeSec()		const;
	bool				vent0()				const;
	bool				vent1()				const;
	bool				vent2()				const;

	void				setO2(					float					newO2);
	void				setCh4(					float					newCh4);
	void				setCO2(					float					newCO2);
	void				setPressure(			float					newPressure);
	void				seTemperatureRespirometer(				float					newTemp1);
	void				setTemperatureSample(				float					newTemp2);
	void				setError(				const QString	&		newError);
	void				setWarning(				const QString	&		newWarning);
	void				setCurChannel(			int						newCurChannel);
	void				setPumpOn(				bool					newPumpOn);
	void				setO2On(				bool					newO2On);
	void				setCO2On(				bool					newCO2On);
	void				setCh4On(				bool					newCh4On);
	void				setInstantPause(		bool					newInstantPause);
	void				setDelayedPause(		bool					newDelayedPause);
	void				setControlWanted(		bool					newControlWanted);
	void				setOutputFolder(		const QString		&	newOutputFolder);
	void				setChannelInit(			const QVariantList	&	newChannelInit);
	void				setChannelRuntimeSec(	int						newChannelRuntimeSec);
	void				setCalibrateCO2(		bool					newCalibrateCO2);
	void				setInternalLeakTest(	bool					newInternalLeakTest);
	void				setInitialHsFlush(		bool					newInitialHsFlush);
	void				setRuntimeSec(			int						newRuntimeSec);
	void				setVent0(				bool					newVent0);
	void				setVent1(				bool					newVent1);
	void				setVent2(				bool					newVent2);
	void				setAllChanPlot(			const QString		&	newAllChanPlot);
	void				setMeasTimePlot(		const QString		&	newMeasTimePlot);
	void				setGroupChanPlot(		const QString		&	newGroupChanPlot);
	void				setChannelStatus(		const QString		&	newChannelStatus);	

	QStringList backlog() const;

	
	QVariantList channelConfs() const;

    QString allChanPlot() const;

    QString measTimePlot() const;

    QString groupChanPlot() const;

    QString channelStatus() const;

	QUrl flowChartFile() const;
	void setFlowChartFile(const QUrl &newFlowChartFile);
	void setFlowChartLocalFile(const QString &newFlowChartFile);
	
	QStringList availablePorts() const;
	
	
	QString chosenPort() const;
	void setChosenPort(const QString &newChosenPort);
	
public slots:
	void				setChannelInit(		int index, bool checked);
	void				push_meas_data();
	void				push_proc_data();
	void				push_current_channel(	int		channel);
	void				push_valve_state(		int		channel, bool valve_open);
	void				push_vent_state(		int		vent,		bool vent_open);
	void				push_pump_state(		bool	pump_on);
	void				push_O2_state(			bool	O2_on);
	void				push_CO2_state(			bool	CO2_on);
	void				push_CH4_state(			bool	CH4_on);
	void				push_generic_info(QString info, QString infoType);
	void				push_error(				QString	error);
	void				push_warning(			QString	warning);
	void				push_info(				QString info);
	void				push_loading_feedback(	QString feedback, bool finished, QString error);
	void				push_datafilepath(		QString datafilepath);
	void				start();
	void				init();
	void				receive_last_values( int relTime, int measuring_channel, float pressure, float flow, float temperatureRespirometer, float temperatureSample, float CO2_ADC, float O2_raw, float CH4_raw, float CO2_raw);
	void				setAvailablePorts(const QStringList &newAvailablePorts);
	QString				choosePort(QStringList);

signals:
	void				O2Changed();
	void				CH4Changed();
	void				CO2Changed();
	void				pressureChanged();
	void				temp1Changed();
	void				temp2Changed();
	void				errorChanged();
	void				warningChanged();
	void				curChannelChanged();
	void				valvesOpenedChanged();
	void				pumpOnChanged();
	void				O2OnChanged();
	void				CO2OnChanged();
	void				CH4OnChanged();
	void				instantPauseChanged(bool);
	void				delayedPauseChanged(bool);
	void				controlWantedChanged(bool);
	void				outputFolderChanged(QString);
	void				modelsLoaded();
	void				showLoading();
	void				cantFindOldDatabase();
	void				feedbackChanged();
	void				channelInitChanged();
	void				channelRuntimeSecChanged();
	void				calibrateCO2Changed();
	void				internalLeakTestChanged();
	void				initialHsFlushChanged();
	void				runtimeSecChanged();
	void				respiroInited();
	void				vent0Changed();
	void				vent1Changed();
	void				vent2Changed();
	void				backlogChanged();

	void				initSignal(
			QString		dataFilePath,
			QList<int>	channels
	);

	void				startSignal(
			int			runtimeSec,
			int			channelRuntimeSec,
			bool		calibrateCO2,
			bool		internalLeakTest,
			bool		initialHsFlush
	);
	
	void channelConfsChanged();
    void allChanPlotChanged();
    void measTimePlotChanged();
    void groupChanPlotChanged();
    void channelStatusChanged();
	void flowChartFileChanged();
	void availablePortsChanged();
	void chosenPortChanged(QString);
	
private:
	void				loadModels();

private:
	Database		*	_db			= nullptr;
	TableModel		*	_dataProc	= nullptr,
					*	_dataMeas	= nullptr,
					*	_msgs		= nullptr;
	int					_curChannel,
						_runtimeSec			= 365 * 24 * 60 * 60,
						_channelRuntimeSec	= 5 * 60;
	float				_O2,
						_CH4,
						_CO2,
						_pressure,
						_temp1,
						_temp2;
	QString				_error,
						_warning,
						_allChanPlot,
						_measTimePlot,
						_groupChanPlot,
						_channelStatus,
						_outputFolder,
						_dataFilePath,
						_chosenPort;
	std::vector<bool>	_valvesOpened;
	bool				_pumpOn,
						_O2On,
						_CO2On,
						_CH4On,
						_instantPause		= false,
						_delayedPause		= false,
						_controlWanted		= false,
						_hardResetFeedback	= false,
						_calibrateCO2		= true,
						_internalLeakTest	= true,
						_initialHsFlush		= false,
						_vent0,
						_vent1,
						_vent2;
	ColumnDefinitions	_dataMeasuredDefs,
						_dataProcessedDefs,
						_msgsDefs;
	Feedbacks			_feedbacks;
	FeedbackMap			_feedbackMap;
	QVariantList		_channelInit		= QVariantList(13, false);
	QStringList			_backlog,	
						_availablePorts;
	ChannelConfs		_channelConfs;
	QUrl				_flowChartFile;
};

#endif // RESPIRO_H
