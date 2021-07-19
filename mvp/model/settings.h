#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings();

    void setFFTSampleWidth(unsigned short width);
    unsigned short setFFTSampleWidth();

    void setFFTBackgroundExec(bool enable);
    bool isFFTBackgroundExec();

    void enableNullHarmonic(bool enable);
    bool isEnableNullHarmonic();

private:
    bool _isEnableFFTBackgroundExec;
    bool _isEnableNullHarmonic;
    unsigned short _sampleWidth;
};

#endif // SETTINGSMODEL_H
