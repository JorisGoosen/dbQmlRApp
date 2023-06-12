#ifndef RESPIRO_H
#define RESPIRO_H

#include <QObject>
#include "tablemodel.h"
#include "labels.h"

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
	Q_PROPERTY(int			o2				READ o2				WRITE setO2				NOTIFY o2Changed			)
	Q_PROPERTY(int			ch4				READ ch4			WRITE setCh4			NOTIFY ch4Changed			)
	Q_PROPERTY(int			co2				READ co2			WRITE setCo2			NOTIFY co2Changed			)
	Q_PROPERTY(int			pressure		READ pressure		WRITE setPressure		NOTIFY pressureChanged		)
	Q_PROPERTY(float		temp1			READ temp1			WRITE setTemp1			NOTIFY temp1Changed			)
	Q_PROPERTY(float		temp2			READ temp2			WRITE settemp2			NOTIFY temp2Changed			)
	Q_PROPERTY(QString		error			READ error			WRITE setError			NOTIFY errorChanged			)
	Q_PROPERTY(QString		warning			READ warning		WRITE setWarning		NOTIFY warningChanged		)

	Q_PROPERTY(int			curChannel		READ curChannel		WRITE setCurChannel		NOTIFY curChannelChanged	)
	Q_PROPERTY(QVariantList valvesOpened	READ valvesOpened							NOTIFY valvesOpenedChanged	) //List of booleans
	Q_PROPERTY(bool			pumpOn			READ pumpOn			WRITE setPumpOn			NOTIFY pumpOnChanged		)
	Q_PROPERTY(bool			o2On			READ o2On			WRITE setO2On			NOTIFY o2OnChanged			)
	Q_PROPERTY(bool			co2On			READ co2On			WRITE setCo2On			NOTIFY co2OnChanged			)
	Q_PROPERTY(bool			ch4On			READ ch4On			WRITE setCh4On			NOTIFY ch4OnChanged			)

	Q_PROPERTY(bool			instantPause	READ instantPause	WRITE setInstantPause	NOTIFY instantPauseChanged	)
	Q_PROPERTY(bool			delayedPause	READ delayedPause	WRITE setDelayedPause	NOTIFY delayedPauseChanged	)
	Q_PROPERTY(bool			controlWanted	READ controlWanted	WRITE setControlWanted	NOTIFY controlWantedChanged	)

	Q_PROPERTY(QString		outputFolder	READ outputFolder	WRITE setOutputFolder	NOTIFY outputFolderChanged	)
	Q_PROPERTY(QStringList	feedback		READ feedback								NOTIFY feedbackChanged		)

public:
	explicit Respiro();

	Q_INVOKABLE	void	startSession();
	Q_INVOKABLE	void	loadOldSession(const QString & oldOutputFolder);

	Q_INVOKABLE	bool	feedbackFinished(	const QString & feedbackMsg);
	Q_INVOKABLE	QString	feedbackError(		const QString & feedbackMsg);


	Database	*		db()			const	{ return _db;		}
	TableModel	*		data()			const	{ return _data;		}
	TableModel	*		msgs()			const	{ return _msgs;		}
	Labels		*		labels()		const	{ return _labels;	}

	int					o2()			const;
	int					ch4()			const;
	int					co2()			const;
	int					pressure()		const;
	float				temp1()			const;
	float				temp2()			const;
	const QString	&	error()			const;
	const QString	&	warning()		const;
	int					curChannel()	const;
	QVariantList		valvesOpened()	const;
	bool				pumpOn()		const;
	bool				o2On()			const;
	bool				co2On()			const;
	bool				ch4On()			const;
	bool				instantPause()	const;
	bool				delayedPause()	const;
	bool				controlWanted()	const;
	const QString	&	outputFolder()	const;
	const QString	&	dbPath()		const;
	QStringList			feedback()		const;

	void				setO2(				int				newO2);
	void				setCh4(				int				newCh4);
	void				setCo2(				int				newCo2);
	void				setPressure(		int				newPressure);
	void				setTemp1(			float			newTemp1);
	void				settemp2(			float			newTemp2);
	void				setError(			const QString & newError);
	void				setWarning(			const QString & newWarning);
	void				setCurChannel(		int				newCurChannel);
	void				setPumpOn(			bool			newPumpOn);
	void				setO2On(			bool			newO2On);
	void				setCo2On(			bool			newCo2On);
	void				setCh4On(			bool			newCh4On);
	void				setInstantPause(	bool			newInstantPause);
	void				setDelayedPause(	bool			newDelayedPause);
	void				setControlWanted(	bool			newControlWanted);
	void				setOutputFolder(	const QString & newOutputFolder);


public slots:
	void				push_raw_data(			int		o2, int ch4, int co2, int pressure, float temp1, float temp2);
	void				push_current_channel(	int		channel);
	void				push_valve_state(		int		channel, bool valve_open);
	void				push_pump_state(		bool	pump_on);
	void				push_o2_state(			bool	o2_on);
	void				push_co2_state(			bool	co2_on);
	void				push_ch4_state(			bool	ch4_on);
	void				push_error(				QString	error);
	void				push_warning(			QString	warning);
	void				push_info(				QString info);
	void				push_loading_feedback(	QString feedback, bool finished, QString error);

signals:
	void				o2Changed();
	void				ch4Changed();
	void				co2Changed();
	void				pressureChanged();
	void				temp1Changed();
	void				temp2Changed();
	void				errorChanged();
	void				warningChanged();
	void				curChannelChanged();
	void				valvesOpenedChanged();
	void				pumpOnChanged();
	void				o2OnChanged();
	void				co2OnChanged();
	void				ch4OnChanged();
	void				instantPauseChanged(bool);
	void				delayedPauseChanged(bool);
	void				controlWantedChanged(bool);
	void				outputFolderChanged(QString);
	void				modelsLoaded();
	void				cantFindOldDatabase();
	void				feedbackChanged();

	void				start(
			QList<int>	channels			= {1,2,3,4,5,6,7,8,9,10,11,12},
			int			runtimeSec			= 365 * 24 * 60 * 60,
			int			channelRuntimeSec	= 5 * 60,
			bool		calibrateCO2		= true,
			bool		internalLeakTest	= true,
			bool		initialHsFlush		= false
	);


private:
	void				loadModels();

private:
	Database		*	_db		= nullptr;
	Labels			*	_labels	= nullptr;
	TableModel		*	_data	= nullptr,
					*	_msgs	= nullptr;
	int					_o2,
						_ch4,
						_co2,
						_pressure,
						_curChannel;
	float				_temp1,
						_temp2;
	QString				_error,
						_warning,
						_outputFolder;
	std::vector<bool>	_valvesOpened;
	bool				_pumpOn,
						_o2On,
						_co2On,
						_ch4On,
						_instantPause		= false,
						_delayedPause		= false,
						_controlWanted		= false,
						_hardResetFeedback	= false;

	ColumnDefinitions	_dataDefs,
						_msgsDefs;

	Feedbacks			_feedbacks;
	FeedbackMap			_feedbackMap;
};

#endif // RESPIRO_H
