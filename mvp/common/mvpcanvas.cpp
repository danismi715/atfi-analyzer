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
    _navigate_panel = new QDockWidget(this);
    _navigate_panel->setTitleBarWidget(new QWidget()); //Delete title
    _navigate_panel->setWindowFlag(Qt::WindowType::FramelessWindowHint);
    _navigate_panel->setWidget(widget);
    _navigate_panel->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);

    if (area == Qt::DockWidgetArea::RightDockWidgetArea || area == Qt::DockWidgetArea::LeftDockWidgetArea) {
        _navigate_panel->setFixedWidth(widget->width());
    }
    if (area == Qt::DockWidgetArea::TopDockWidgetArea || area == Qt::DockWidgetArea::BottomDockWidgetArea) {
        _navigate_panel->setFixedHeight(widget->height());
    }

    addDockWidget(area, _navigate_panel);
}

QWidget *MVPCanvas::getNavigatePanel()
{
    return _navigate_panel;
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
