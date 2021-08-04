#include "mvp/common/router.h"
#include <QMainWindow>

router::Router::Router()
{

}

router::Router &router::Router::getInstance()
{
    static Router instance;
    return instance;
}

QString router::Router::getCurrentScreenName()
{
    return _current_screen;
}

void router::Router::setCanvas(MVPCanvas *canvas)
{
    _canvas = canvas;
}

void router::Router::makeRedirection(QString &&screenName)
{
    if (_routes.find(screenName) != _routes.end()) {
       _current_presenter = _routes.find(screenName)->second;
    }

    _current_presenter->exec();
    _canvas->setCurrentScreenByID(_current_presenter->getViewId());
}

void router::Router::makeScreenRoute(QString &&screen_name, PresenterBase *ppresenter, ViewBase *pview, Model *pmodel)
{
    int viewid = _canvas->addScreen(dynamic_cast<QWidget*>(pview));

    ppresenter->bindView(pview, viewid);
    ppresenter->bindModel(pmodel);

    _routes[screen_name] = ppresenter;
}

void router::Router::setDefaultScreen(QString &&default_screen)
{
    _default_screen = default_screen;
}

void router::Router::exec()
{
    makeRedirection(std::move(_default_screen));
    _canvas->showMaximized();
}
