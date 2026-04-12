#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>

class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList 	qmlsShown 	READ qmlsShown 							NOTIFY qmlsShownChanged)
	Q_PROPERTY(bool 		hasPlots 	READ hasPlots 		WRITE setHasPlots 	NOTIFY hasPlotsChanged)

public:
	explicit MainModel(QObject *parent = nullptr);

	QStringList qmlsShown() const;

	bool hasPlots() const;
	void setHasPlots(bool newHasPlots);
	
public slots:
	void inited()			{ setQmlsShown( {"ChannelConf"						}); }
	void dbLoaded()			{ setQmlsShown( {"Loading"				, "Plots"	}); }
	void modelsLoaded()		{ setQmlsShown( {"Loading",	 	"Data"	, "Plots"	}); }
	void respiroInited()	{ setQmlsShown( {				"Data"	, "Plots"	}); }
	void closing();
	void enableHasPlot()	{ setHasPlots(true); }
	
signals:
	void qmlsShownChanged();
	void exitR();

	void hasPlotsChanged();
	
private:
	void setQmlsShown(const QStringList & newQmlsShown);

    QStringList _qmlsShown = { "Init"}; //, "Hardware"
	bool _hasPlots = false;
};

#endif // MAINMODEL_H
