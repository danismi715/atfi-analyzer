#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QStackedLayout>
#include "mvp/model/model.h"
#include "view.h"
#include "presenter.h"
#include "mvp/common/mvpcanvas.h"
#include <tuple>

class Model;
class PresenterBase;
class ViewBase;

namespace router {

class Router
{
public:
    Router(const Router&) = delete;
    Router(const Router&&) = delete;

    Router& operator=(const Router&) = delete;
    Router&& operator=(const Router&&) = delete;

    static Router& getInstance();
    QString getCurrentScreenName();

    void setCanvas(MVPCanvas *canvas);
    void makeRedirection(QString &&screenName);
    void makeScreenRoute(QString &&screenName, PresenterBase *ppresenter, ViewBase *pview, Model *pmodel);
    void setDefaultScreen(QString &&defaultScreen);
    void exec();
private:
    Router();

    std::map<QString, PresenterBase*> _routes;
    QString _currentScreen;
    Model *_currentModel;
    PresenterBase *_currentPresenter;
    ViewBase *_currentView;
    MVPCanvas *_canvas;
    QString _defaultScreen;
};

}
#endif // ROUTER_H
