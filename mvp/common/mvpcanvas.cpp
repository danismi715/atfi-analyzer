#include "mvp/common/mvpcanvas.h"
#include <QDockWidget>
#include <QGraphicsDropShadowEffect>

MVPCanvas::MVPCanvas(QWidget *parent) : MVPCanvas(640, 480, parent)
{

}

MVPCanvas::MVPCanvas(int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , _width(width)
    , _height(height)
{
    setCentralWidget(&_stackscreen);
    resize(_width, _height);
}

void MVPCanvas::setWindowWidth(int width)
{
    _width = width;
}

void MVPCanvas::setWindowHeight(int height)
{
    _height = height;
}

void MVPCanvas::addNavigatePanel(Qt::DockWidgetArea area, QWidget *widget)
{
    _navigatePanel = new QDockWidget(this);
    _navigatePanel->setTitleBarWidget(new QWidget()); //Delete title
    _navigatePanel->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    _navigatePanel->setWidget(widget);
    _navigatePanel->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);

    if (area == Qt::DockWidgetArea::RightDockWidgetArea || area == Qt::DockWidgetArea::LeftDockWidgetArea) {
        _navigatePanel->setFixedWidth(widget->width());
    }
    if (area == Qt::DockWidgetArea::TopDockWidgetArea || area == Qt::DockWidgetArea::BottomDockWidgetArea) {
        _navigatePanel->setFixedHeight(widget->height());
    }

    addDockWidget(area, _navigatePanel);
}

QWidget *MVPCanvas::getNavigatePanel()
{
    return _navigatePanel;
}

int MVPCanvas::addScreen(QWidget *screen)
{
    return _stackscreen.addWidget(screen);
}

void MVPCanvas::show()
{
    QMainWindow::show();
}

void MVPCanvas::setCurrentScreenByID(int id)
{
    _stackscreen.setCurrentIndex(id);
}

void MVPCanvas::showMaximized()
{
    QMainWindow::showMaximized();
}
