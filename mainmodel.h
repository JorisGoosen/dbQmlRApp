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
	void modelsLoaded() { setQmlsShown( {"Data", "Hardware" }); }

signals:
	void qmlsShownChanged();

private:
	void setQmlsShown(const QStringList & newQmlsShown);

	QStringList _qmlsShown = { "Init", "Hardware" };
};

#endif // MAINMODEL_H
