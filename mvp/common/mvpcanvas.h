#ifndef MVPCANVAS_H
#define MVPCANVAS_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGridLayout>
#include "mvp/components/navigatepanel/navigatepanel.h"

class MVPCanvas : public QMainWindow
{
    Q_OBJECT
public:
    explicit MVPCanvas(QWidget *parent = nullptr);
    explicit MVPCanvas(int width, int height, QWidget *parent = nullptr);

    void setWindowWidth(int width);
    void setWindowHeight(int height);
    void addNavigatePanel(Qt::DockWidgetArea area, QWidget *widget);
    QWidget *getNavigatePanel();
    int addScreen(QWidget *screen);
    void setCurrentScreenByID(int id);
    void show();
    void showMaximized();
private:
    QStackedWidget _stackscreen;
    QDockWidget *_navigate_panel;
    int _width;
    int _height;
};

#endif // MVPCANVAS_H
