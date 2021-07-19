#ifndef MAINSCREENPRESENTER_H
#define MAINSCREENPRESENTER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "mvp/common/presenter.h"
#include "mvp/gui/view/dashboardscreen/dashboardscreenview.h"
#include <complex>
#include <fftw3.h>

class DashboardScreenView;

class DashboardScreenPresenter : public QObject, public PresenterBase
{
    Q_OBJECT

public:
    DashboardScreenPresenter();
    void postbinding() override;
    void setDataChart();
    void pollFileReadProgress();

public slots:
    void openFileEventHandler(QString name);
    void setParamEventHandler(int value);
    void mouseWheelEventHandler(QWheelEvent* event);
    void exportEventHandler();
    void fft();

private:
    QVector<double> _y;
    QVector<double> _x;

    QVector<double> _fft;
    QVector<double> _freq;

    QTimer *_timer;
    int _startPosition;
};

#endif // MAINSCREENPRESENTER_H
