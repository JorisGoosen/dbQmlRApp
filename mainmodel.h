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
	void modelsLoaded()		{ setQmlsShown( {"Loading", "Data", "Hardware" }); }
	void respiroInited()	{ setQmlsShown( {			"Data", "Hardware" }); }
	void closing();

signals:
	void qmlsShownChanged();
	void exitR();

private:
	void setQmlsShown(const QStringList & newQmlsShown);

	QStringList _qmlsShown = { "Init", "Hardware" };
};

#endif // MAINMODEL_H
