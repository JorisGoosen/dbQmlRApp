#include "channel.h"

Channel::Channel(int channelID, QObject *parent)
    : QObject{parent}
    , _channelID(channelID)
    , _sampleID("")
    , _hsVol_ml(std::nan(""))
    , _CO2max_ppm(std::nan(""))
    , _O2min_perc(std::nan(""))
    , _O2max_perc(std::nan(""))
    , _CH4max_ppm(std::nan(""))
    , _leakPass(false)
    , _pressPass(false)
    , _volPass(false)
    , _measureStable(true)
    , _isActive(false)
    , _inExperiment(false)
    , _cycle(0)
    , _startTime(0)
    , _completeCycle(0)
    , _statusText("")
    , _color("")
{
}

int Channel::channelID() const { return _channelID; }
QString Channel::sampleID() const { return _sampleID; }
double Channel::hsVol_ml() const { return _hsVol_ml; }
double Channel::CO2max_ppm() const { return _CO2max_ppm; }
double Channel::O2min_perc() const { return _O2min_perc; }
double Channel::O2max_perc() const { return _O2max_perc; }
double Channel::CH4max_ppm() const { return _CH4max_ppm; }
bool Channel::leakPass() const { return _leakPass; }
bool Channel::pressPass() const { return _pressPass; }
bool Channel::volPass() const { return _volPass; }
bool Channel::measureStable() const { return _measureStable; }
bool Channel::isActive() const { return _isActive; }
bool Channel::inExperiment() const { return _inExperiment; }
double Channel::cycle() const { return _cycle; }
double Channel::startTime() const { return _startTime; }
double Channel::completeCycle() const { return _completeCycle; }
QString Channel::statusText() const { return _statusText; }
QString Channel::color() const { return _color; }

void Channel::setSampleID(const QString &sampleID) {
    if (_sampleID == sampleID) return;
    _sampleID = sampleID;
    emit sampleIDChanged();
}

void Channel::setHsVol_ml(double hsVol_ml) {
    if (qFuzzyCompare(_hsVol_ml, hsVol_ml)) return;
    _hsVol_ml = hsVol_ml;
    emit hsVol_mlChanged();
}

void Channel::setCO2max_ppm(double CO2max_ppm) {
    if (qFuzzyCompare(_CO2max_ppm, CO2max_ppm)) return;
    _CO2max_ppm = CO2max_ppm;
    emit CO2max_ppmChanged();
}

void Channel::setO2min_perc(double O2min_perc) {
    if (qFuzzyCompare(_O2min_perc, O2min_perc)) return;
    _O2min_perc = O2min_perc;
    emit O2min_percChanged();
}

void Channel::setO2max_perc(double O2max_perc) {
    if (qFuzzyCompare(_O2max_perc, O2max_perc)) return;
    _O2max_perc = O2max_perc;
    emit O2max_percChanged();
}

void Channel::setCH4max_ppm(double CH4max_ppm) {
    if (qFuzzyCompare(_CH4max_ppm, CH4max_ppm)) return;
    _CH4max_ppm = CH4max_ppm;
    emit CH4max_ppmChanged();
}

void Channel::setLeakPass(bool leakPass) {
    if (_leakPass == leakPass) return;
    _leakPass = leakPass;
    emit leakPassChanged();
}

void Channel::setPressPass(bool pressPass) {
    if (_pressPass == pressPass) return;
    _pressPass = pressPass;
    emit pressPassChanged();
}

void Channel::setVolPass(bool volPass) {
    if (_volPass == volPass) return;
    _volPass = volPass;
    emit volPassChanged();
}

void Channel::setMeasureStable(bool measureStable) {
    if (_measureStable == measureStable) return;
    _measureStable = measureStable;
    emit measureStableChanged();
}

void Channel::setActive(bool isActive) {
    if (_isActive == isActive) return;
    _isActive = isActive;
    emit isActiveChanged();
}

void Channel::setInExperiment(bool inExperiment) {
    if (_inExperiment == inExperiment) return;
    _inExperiment = inExperiment;
    emit inExperimentChanged();
}

void Channel::setCycle(double cycle) {
    if (qFuzzyCompare(_cycle, cycle)) return;
    _cycle = cycle;
    emit cycleChanged();
}

void Channel::setStartTime(double startTime) {
    if (qFuzzyCompare(_startTime, startTime)) return;
    _startTime = startTime;
    emit startTimeChanged();
}

void Channel::setCompleteCycle(double completeCycle) {
    if (qFuzzyCompare(_completeCycle, completeCycle)) return;
    _completeCycle = completeCycle;
    emit completeCycleChanged();
}

void Channel::setStatusText(const QString &statusText) {
    if (_statusText == statusText) return;
    _statusText = statusText;
    emit statusTextChanged();
}

void Channel::setColor(const QString &color) {
    if (_color == color) return;
    _color = color;
    emit colorChanged();
}

#include "channel.moc"
