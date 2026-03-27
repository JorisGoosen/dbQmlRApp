#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>

class MainModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList qmlsShown READ qmlsShown NOTIFY qmlsShownChanged)

public:
	explicit MainModel(QObject *parent = nullptr);

	QStringList qmlsShown() const;

public slots:
	void inited()			{ setQmlsShown( {"ChannelConf"						}); }
	void dbLoaded()			{ setQmlsShown( {"Loading"				, "Plots"	}); }
	void modelsLoaded()		{ setQmlsShown( {"Loading",	 	"Data"	, "Plots"	}); }
	void respiroInited()	{ setQmlsShown( {				"Data"	, "Plots"	}); }
	void closing();

signals:
	void qmlsShownChanged();
	void exitR();

private:
	void setQmlsShown(const QStringList & newQmlsShown);

	QStringList _qmlsShown = { "Init" }; //, "Hardware"
};

#endif // MAINMODEL_H
