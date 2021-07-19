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
    return _currentScreen;
}

void router::Router::setCanvas(MVPCanvas *canvas)
{
    _canvas = canvas;
}

void router::Router::makeRedirection(QString &&screenName)
{
    if (_routes.find(screenName) != _routes.end()) {
       _currentPresenter = _routes.find(screenName)->second;
    }

    _currentPresenter->exec();
    _canvas->setCurrentScreenByID(_currentPresenter->getViewId());
}

void router::Router::makeScreenRoute(QString &&screenName, PresenterBase *ppresenter, ViewBase *pview, Model *pmodel)
{
    int viewid = _canvas->addScreen(dynamic_cast<QWidget*>(pview));

    ppresenter->bindView(pview, viewid);
    ppresenter->bindModel(pmodel);

    _routes[screenName] = ppresenter;
}

void router::Router::setDefaultScreen(QString &&defaultScreen)
{
    _defaultScreen = defaultScreen;
}

void router::Router::exec()
{
    makeRedirection(std::move(_defaultScreen));
    _canvas->showMaximized();
}
