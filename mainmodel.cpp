#include "mainmodel.h"

MainModel::MainModel(QObject *parent)
	: QObject{parent}
{

}

QStringList MainModel::qmlsShown() const
{
	return _qmlsShown;
}

void MainModel::setQmlsShown(const QStringList & newQmlsShown)
{
	if (_qmlsShown == newQmlsShown)
		return;

	_qmlsShown = newQmlsShown;
	emit qmlsShownChanged();
}
