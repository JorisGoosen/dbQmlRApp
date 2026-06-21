#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>

class Channel : public QObject
{
    Q_OBJECT
    
    Q_PROPERTY(int channelID READ channelID CONSTANT)
    Q_PROPERTY(QString sampleID READ sampleID NOTIFY sampleIDChanged)
    Q_PROPERTY(double hsVol_ml READ hsVol_ml NOTIFY hsVol_mlChanged)
    Q_PROPERTY(double CO2max_ppm READ CO2max_ppm NOTIFY CO2max_ppmChanged)
    Q_PROPERTY(double O2min_perc READ O2min_perc NOTIFY O2min_percChanged)
    Q_PROPERTY(double O2max_perc READ O2max_perc NOTIFY O2max_percChanged)
    Q_PROPERTY(double CH4max_ppm READ CH4max_ppm NOTIFY CH4max_ppmChanged)
    Q_PROPERTY(bool leakPass READ leakPass NOTIFY leakPassChanged)
    Q_PROPERTY(bool pressPass READ pressPass NOTIFY pressPassChanged)
    Q_PROPERTY(bool volPass READ volPass NOTIFY volPassChanged)
    Q_PROPERTY(bool measureStable READ measureStable NOTIFY measureStableChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    Q_PROPERTY(bool inExperiment READ inExperiment NOTIFY inExperimentChanged)
    Q_PROPERTY(double cycle READ cycle NOTIFY cycleChanged)
    Q_PROPERTY(double startTime READ startTime NOTIFY startTimeChanged)
    Q_PROPERTY(double completeCycle READ completeCycle NOTIFY completeCycleChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    Q_PROPERTY(QString color READ color NOTIFY colorChanged)

public:
    explicit Channel(int channelID, QObject *parent = nullptr);

    int channelID() const;
    QString sampleID() const;
    double hsVol_ml() const;
    double CO2max_ppm() const;
    double O2min_perc() const;
    double O2max_perc() const;
    double CH4max_ppm() const;
    bool leakPass() const;
    bool pressPass() const;
    bool volPass() const;
    bool measureStable() const;
    bool isActive() const;
    bool inExperiment() const;
    double cycle() const;
    double startTime() const;
    double completeCycle() const;
    QString statusText() const;
    QString color() const;

    void setSampleID(const QString &sampleID);
    void setHsVol_ml(double hsVol_ml);
    void setCO2max_ppm(double CO2max_ppm);
    void setO2min_perc(double O2min_perc);
    void setO2max_perc(double O2max_perc);
    void setCH4max_ppm(double CH4max_ppm);
    void setLeakPass(bool leakPass);
    void setPressPass(bool pressPass);
    void setVolPass(bool volPass);
    void setMeasureStable(bool measureStable);
    void setActive(bool isActive);
    void setInExperiment(bool inExperiment);
    void setCycle(double cycle);
    void setStartTime(double startTime);
    void setCompleteCycle(double completeCycle);
    void setStatusText(const QString &statusText);
    void setColor(const QString &color);

signals:
    void sampleIDChanged();
    void hsVol_mlChanged();
    void CO2max_ppmChanged();
    void O2min_percChanged();
    void O2max_percChanged();
    void CH4max_ppmChanged();
    void leakPassChanged();
    void pressPassChanged();
    void volPassChanged();
    void measureStableChanged();
    void isActiveChanged();
    void inExperimentChanged();
    void cycleChanged();
    void startTimeChanged();
    void completeCycleChanged();
    void statusTextChanged();
    void colorChanged();

private:
    int _channelID;
    QString _sampleID;
    double _hsVol_ml;
    double _CO2max_ppm;
    double _O2min_perc;
    double _O2max_perc;
    double _CH4max_ppm;
    bool _leakPass;
    bool _pressPass;
    bool _volPass;
    bool _measureStable;
    bool _isActive;
    bool _inExperiment;
    double _cycle;
    double _startTime;
    double _completeCycle;
    QString _statusText;
    QString _color;
};

typedef std::vector<Channel*> Channels;

Q_DECLARE_METATYPE(Channel*)

#endif
