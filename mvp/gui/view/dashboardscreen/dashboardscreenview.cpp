#include <QString>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QGraphicsDropShadowEffect>
#include "mvp/gui/view/dashboardscreen/dashboardscreenview.h"

DashboardScreenView::DashboardScreenView(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    setAutoFillBackground(true);

    // Create plot for ECG
    _ecgPlot = new CustomChart(this, "ECG", "x", "y");
    _fftPlot = new CustomChart(this, "FFT", "x", "y");

    _ecgPlot->setBaseSize(QSize(1280, 400));
    _ecgPlot->setMinimumSize(QSize(1280, 400));
    _ecgPlot->setMaximumSize(QSize(1280, 400));

    _ecgPlot->replot();

    _fftPlot->setBaseSize(QSize(1280, 400));
    _fftPlot->setMinimumSize(QSize(1280, 400));
    _fftPlot->setMaximumSize(QSize(1280, 400));

    _fftPlot->setInteraction(QCP::iRangeZoom);
    _fftPlot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    _fftPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));

    _fftPlot->replot();

    // Create OpenFile Button
    _openFileButton = new QPushButton("Open file");
    _openFileButton->setMaximumSize(QSize(80, 25));

    // Create Trace Button
    _traceButton = new QPushButton("Trace");
    _traceButton->setMaximumSize(QSize(80, 25));

    _exportButton = new QPushButton("Export");
    _traceButton->setMaximumSize(QSize(80, 25));

    // Create line for entering text
    _startPositionParam = new QLineEdit();
    _startPositionParam->setMaximumSize(QSize(80, 25));

    // Create progress bar
    _fileReadProgress = new QProgressBar;
    _fileReadProgress->setRange(0, 100);
    _fileReadProgress->setValue(0);
    _fileReadProgress->setMinimumSize(QSize(180, 25));

    QGraphicsDropShadowEffect* dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setBlurRadius(10);
    dropShadowEffect->setColor(QColor(0, 0, 0));
    dropShadowEffect->setXOffset(0);
    dropShadowEffect->setYOffset(0);

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addWidget(_openFileButton);
    groupLayout->addWidget(_startPositionParam);
    groupLayout->addWidget(_traceButton);
    groupLayout->addWidget(_fileReadProgress);
    groupLayout->addWidget(_exportButton);

    QGroupBox *groupUserInt = new QGroupBox;
    groupUserInt->setLayout(groupLayout);
    groupUserInt->setGraphicsEffect(dropShadowEffect);

    QGridLayout *grid = new QGridLayout();    

    grid->addWidget(groupUserInt, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignTop);
    grid->addWidget(_ecgPlot, 0, 1, 1, 1, Qt::AlignRight | Qt::AlignTop);
    grid->addWidget(_fftPlot, 1, 1, 1, 1, Qt::AlignRight | Qt::AlignTop);
    mainWidget->setLayout(grid);

    connect(_ecgPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SIGNAL(mouseWheelEvent(QWheelEvent*)));
    connect(_exportButton, SIGNAL(clicked()), this, SIGNAL(exportButtonClickedEvent()));
    connect(_openFileButton, SIGNAL(clicked()), this, SLOT(openFileDialogHandler()));
    connect(_traceButton, SIGNAL(clicked()), this, SLOT(analyzeButtonHandler()));
}

DashboardScreenView::~DashboardScreenView()
{
}

void DashboardScreenView::show()
{
    QMainWindow::show();
}

void DashboardScreenView::update()
{
}

void DashboardScreenView::exit()
{
}

void DashboardScreenView::setECGSeries(QVector<double>&& x, QVector<double>&& y)
{
    _ecgPlot->graph(0)->setData(x, y, true);
    _ecgPlot->rescaleAxes();
    _ecgPlot->replot();
}

void DashboardScreenView::setFFTSeries(QVector<double> &&x, QVector<double> &&y)
{
    _fftPlot->graph(0)->setData(x, y, true);
    _fftPlot->rescaleAxes();
    _fftPlot->replot();
}

void DashboardScreenView::setFileReadProgress(int value)
{
    _fileReadProgress->setValue(value);
}

void DashboardScreenView::openFileDialogHandler()
{
    emit openFileEvent(QFileDialog::getOpenFileName(this));
}

void DashboardScreenView::analyzeButtonHandler()
{
    emit setParamEvent(_startPositionParam->text().toInt());
}
