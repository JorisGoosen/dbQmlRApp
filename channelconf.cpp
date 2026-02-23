#include "channelconf.h"
#include "rwrapper.h"

ChannelConf::ChannelConf(int channelID, RWrapper * rWrapper)
	: QObject{rWrapper}
	, _channelID(channelID)
{
	connect(this, &ChannelConf::getStringFromChannelConf, rWrapper, &RWrapper::getStringFromChannelConf,	Qt::BlockingQueuedConnection);
	connect(this, &ChannelConf::getDoubleFromChannelConf, rWrapper, &RWrapper::getDoubleFromChannelConf,	Qt::BlockingQueuedConnection);
	connect(this, &ChannelConf::setStringIntoChannelConf, rWrapper, &RWrapper::setStringIntoChannelConf,	Qt::BlockingQueuedConnection);
	connect(this, &ChannelConf::setDoubleIntoChannelConf, rWrapper, &RWrapper::setDoubleIntoChannelConf,	Qt::BlockingQueuedConnection);
	
}

int ChannelConf::channelID()
{
	return _channelID;
}

QString ChannelConf::sampleID()
{
	return emit getStringFromChannelConf(_channelID, "sampleID");
}

void ChannelConf::setSampleID(const QString &newSampleID)
{
	if (sampleID() == newSampleID)
		return;
	
	emit setStringIntoChannelConf(_channelID, "sampleID", newSampleID);
	emit sampleIDChanged();
}

double ChannelConf::hsVol_ml() 
{
	return emit getDoubleFromChannelConf(_channelID, "hsVol_ml");
}

void ChannelConf::setHsVol_ml(double newHsVol_ml)
{
	if (qFuzzyCompare(hsVol_ml(), newHsVol_ml))
		return;
	
	emit setDoubleIntoChannelConf(_channelID, "hsVol_ml", newHsVol_ml);
	emit hsVol_mlChanged();
}

double ChannelConf::CO2max_ppm()
{
	return emit getDoubleFromChannelConf(_channelID, "CO2max_ppm");
}

void ChannelConf::setCO2max_ppm(double newCO2max_ppm)
{
	if (qFuzzyCompare(CO2max_ppm(), newCO2max_ppm))
		return;
	
	emit setDoubleIntoChannelConf(_channelID, "CO2max_ppm", newCO2max_ppm);
	emit CO2max_ppmChanged();
}

double ChannelConf::O2min_perc()
{
	return emit getDoubleFromChannelConf(_channelID, "O2min_perc");
}

void ChannelConf::setO2min_perc(double newO2min_perc)
{
	if (qFuzzyCompare(O2min_perc(), newO2min_perc))
		return;
	
	emit setDoubleIntoChannelConf(_channelID, "O2min_perc", newO2min_perc);
	emit O2min_percChanged();
}

double ChannelConf::O2max_perc()
{
	return emit getDoubleFromChannelConf(_channelID, "O2max_perc");
}

void ChannelConf::setO2max_perc(double newO2max_perc)
{
	if (qFuzzyCompare(O2max_perc(), newO2max_perc))
		return;
	
	emit setDoubleIntoChannelConf(_channelID, "O2max_perc", newO2max_perc);
	emit O2min_percChanged();
}

double ChannelConf::CH4max_ppm()
{
	return emit getDoubleFromChannelConf(_channelID, "CH4max_ppm");
}

void ChannelConf::setCH4max_ppm(double newCH4max_ppm)
{
	if (qFuzzyCompare(CH4max_ppm(), newCH4max_ppm))
		return;
	
	emit setDoubleIntoChannelConf(_channelID, "CH4max_ppm", newCH4max_ppm);
	emit CH4max_ppmChanged();
}
