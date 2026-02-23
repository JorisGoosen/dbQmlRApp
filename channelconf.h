#ifndef CHANNELCONF_H
#define CHANNELCONF_H

#include <QObject>

class RWrapper;

class ChannelConf : public QObject
{
	Q_OBJECT
	
	Q_PROPERTY(int		channelID				READ channelID									CONSTANT						)
	Q_PROPERTY(QString	sampleID				READ sampleID			WRITE setSampleID		NOTIFY sampleIDChanged			)
	Q_PROPERTY(double	hsVol_ml				READ hsVol_ml			WRITE setHsVol_ml		NOTIFY hsVol_mlChanged			)
	Q_PROPERTY(double	CO2max_ppm				READ CO2max_ppm			WRITE setCO2max_ppm		NOTIFY CO2max_ppmChanged		)
	Q_PROPERTY(double	O2min_perc				READ O2min_perc			WRITE setO2min_perc		NOTIFY O2min_percChanged		)
	Q_PROPERTY(double	O2max_perc				READ O2max_perc			WRITE setO2max_perc		NOTIFY O2max_percChanged		)
	Q_PROPERTY(double	CH4max_ppm				READ CH4max_ppm			WRITE setCH4max_ppm		NOTIFY CH4max_ppmChanged		)
	
public:

	explicit	ChannelConf(int channeldID, RWrapper * rWrapper);
	
	int			channelID()			;
	QString		sampleID()			;
	double		hsVol_ml()			;
	double		CO2max_ppm()		;
	double		O2min_perc()		;
	double		O2max_perc()		;
	double		CH4max_ppm()		;
	
	void		setSampleID(	const QString &	newSampleID);
	void		setHsVol_ml(	double			newHsVol_ml);
	void		setCO2max_ppm(	double			newCO2max_ppm);
	void		setO2min_perc(	double			newO2min_perc);
	void		setO2max_perc(	double			newO2max_perc);
	void		setCH4max_ppm(	double			newCH4max_ppm);
	
	
	
	
signals:
	void		sampleIDChanged();
	void		hsVol_mlChanged();
	void		CO2max_ppmChanged();
	void		O2min_percChanged();
	void		O2max_percChanged();
	void		CH4max_ppmChanged();
	
	QString		getStringFromChannelConf(int channelID, const QString & confName);
	void		setStringIntoChannelConf(int channelID, const QString & confName, const QString & setting);
	
	double		getDoubleFromChannelConf(int channelID, const QString & confName);
	void		setDoubleIntoChannelConf(int channelID, const QString & confName, const double setting);
	
private:
	int			_channelID = -1;
};

typedef std::vector<ChannelConf*> ChannelConfs;

#endif // DATABASE_H
