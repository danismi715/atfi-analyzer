#ifndef MAINSCREENVIEW_H
#define MAINSCREENVIEW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QChartView>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include "qcustomplot.h"
#include "mvp/common/view.h"
#include "mvp/gui/presenter/dashboardscreen/dashboardscreenpresenter.h"
#include "mvp/components/customchart/customchart.h"

class DashboardScreenView : public QMainWindow, public ViewBase
{
    Q_OBJECT

public:
    explicit DashboardScreenView(QWidget *parent = nullptr);
    ~DashboardScreenView();
    void show() override;
    void update() override;
    void exit() override;

    void setECGSeries(QVector<double>&& x, QVector<double>&& y);
    void setFFTSeries(QVector<double>&& x, QVector<double>&& y);
    void setFileReadProgress(int value);

signals:
    void openFileEvent(QString);
    void setParamEvent(int);
    void mouseWheelEvent(QWheelEvent *mouseEvent);
    void fftButtonClickedEvent();
    void exportButtonClickedEvent();

private slots:
    void openFileDialogHandler();
    void analyzeButtonHandler();

private:
    CustomChart *_ecgPlot;
    CustomChart *_fftPlot;
    QPushButton *_openFileButton;
    QPushButton *_traceButton;
    QPushButton *_exportButton;
    QLineEdit *_startPositionParam;
    QProgressBar *_fileReadProgress;
};

#endif // MAINSCREENVIEW_H
