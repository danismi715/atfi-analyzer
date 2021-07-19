#include "dashboardscreenpresenter.h"
#include <QString>
#include <QDebug>
#include <QVector>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QDir>
#include <math.h>


DashboardScreenPresenter::DashboardScreenPresenter()
    : _startPosition(0)
{
    _timer = new QTimer(this);
    _timer->setInterval(500);
    _fft.clear();
    _freq.clear();
    _x.clear();
    _y.clear();
}

void DashboardScreenPresenter::postbinding()
{
    connect(dynamic_cast<DashboardScreenView*>(_view), SIGNAL(openFileEvent(QString)), this, SLOT(openFileEventHandler(QString)));
    connect(dynamic_cast<DashboardScreenView*>(_view), SIGNAL(setParamEvent(int)), this, SLOT(setParamEventHandler(int)));
    connect(dynamic_cast<DashboardScreenView*>(_view), SIGNAL(mouseWheelEvent(QWheelEvent*)), this, SLOT(mouseWheelEventHandler(QWheelEvent*)));
    connect(dynamic_cast<DashboardScreenView*>(_view), SIGNAL(exportButtonClickedEvent()), this, SLOT(exportEventHandler()));
    connect(_timer, &QTimer::timeout, this, &DashboardScreenPresenter::pollFileReadProgress);
}

void DashboardScreenPresenter::setDataChart()
{
    _y = _model->getY(_startPosition, 2048);
    _x = _model->getX(_startPosition, 2048);

    dynamic_cast<DashboardScreenView*>(_view)->setECGSeries(std::move(_x), std::move(_y));

    fft();
}

void DashboardScreenPresenter::pollFileReadProgress()
{
    int progress = _model->getProgressReadFile();
    dynamic_cast<DashboardScreenView*>(_view)->setFileReadProgress(progress);
}

void DashboardScreenPresenter::fft()
{
    int input_size = 2048;

    fftw_complex *in, *out;
    _fft.clear();
    _freq.clear();

    in = new fftw_complex[input_size];
    out = new fftw_complex[input_size];

    // Initialize 'in' with N complex entries
    fftw_plan my_plan;
    my_plan = fftw_plan_dft_1d(input_size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    int j = 0;
    for (auto i : _y) {
        in[j][0] = i;
        in[j][1] = 0;
        j++;
    }

    fftw_execute(my_plan);

    for (int i = 0; i < input_size / 2; i++) {
        _fft.append(sqrtl(pow(out[i][0], 2) + pow(out[i][1], 2)) / 1024.0f);
        _freq.append(double(double(i) * double(128.0f/ 2048.0f)));
    }
    _fft[0] /= 2;

    dynamic_cast<DashboardScreenView*>(_view)->setFFTSeries(std::move(_freq), std::move(_fft));

    fftw_destroy_plan(my_plan);
    delete [] in;
    delete [] out;
}

void DashboardScreenPresenter::setParamEventHandler(int value)
{
    if ( ((_startPosition + value) <= _model->getSize()) && ((_startPosition + value) >= 0)) {
        _startPosition = value;
        setDataChart();
    }
}

void DashboardScreenPresenter::mouseWheelEventHandler(QWheelEvent *event)
{
    int offset = event->angleDelta().y() / 8;

    if ( ((_startPosition + offset + 2048) < _model->getSize()) && ((_startPosition + offset) >= 0)) {
        _startPosition += offset;
        setDataChart();
    }
}

void DashboardScreenPresenter::exportEventHandler()
{
    QString path = QDir::currentPath() + "/" + QString::number(QDateTime::currentDateTime().toTime_t()) + ".csv";
    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);

    if (_freq.isEmpty()) {
        return;
    }

    for (uint32_t i = 0; i < 1024; i++) {
        out << _freq[i] << '\t' << _fft[i] << endl;
    }

    file.close();
}

void DashboardScreenPresenter::openFileEventHandler(QString name)
{
    if (name.isEmpty()) {
        return;
    }

    _model->setResourceFile(name);

    QThread *modelExtractDataThread = QThread::create([](Model *pmodel) {
        pmodel->extractResourceFromFile(CHANNEL_COLUMN_1);
    }, _model);

    _timer->start();
    modelExtractDataThread->start(QThread::Priority::HighPriority);
}
