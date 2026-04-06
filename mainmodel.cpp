#include "mainmodel.h"

MainModel::MainModel(QObject *parent)
	: QObject{parent}
{

}

QStringList MainModel::qmlsShown() const
{
	return _qmlsShown;
}

void MainModel::closing()
{
	setQmlsShown({});

	emit exitR();
}

void MainModel::setQmlsShown(const QStringList & newQmlsShown)
{
	if (_qmlsShown == newQmlsShown)
		return;

	_qmlsShown = newQmlsShown;
	emit qmlsShownChanged();
}

bool MainModel::hasPlots() const
{
	return _hasPlots;
}

void MainModel::setHasPlots(bool newHasPlots)
{
	if (_hasPlots == newHasPlots)
		return;
	_hasPlots = newHasPlots;
	emit hasPlotsChanged();
	
	if(!_qmlsShown.contains("Plots"))
		_qmlsShown.append("Plots");
	
	emit qmlsShownChanged();
}
