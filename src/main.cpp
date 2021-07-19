#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QSplashScreen>
#include "mvp/model/model.h"
#include "mvp/common/router.h"
#include "mvp/common/presenter.h"
#include "mvp/gui/view/dashboardscreen/dashboardscreenview.h"
#include "mvp/gui/presenter/dashboardscreen/dashboardscreenpresenter.h"
#include "mvp/gui/view/setupscreen/setupscreenview.h"
#include "mvp/gui/presenter/setupscreen/setupscreenpresenter.h"
#include <fftw3.h>

void setupNavigatePanel(NavigatePanel *pnavigatePanel);
void setupAppStyle(QApplication *papp, const QString stylePath);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setupAppStyle(&app, ":/style.qss");

    NavigatePanel *navigatePanel = new NavigatePanel(NavigatePanel::Horizontal, nullptr);
    MVPCanvas *mvpcanvas = new MVPCanvas(640, 480);

    mvpcanvas->addNavigatePanel(Qt::DockWidgetArea::BottomDockWidgetArea, navigatePanel);

    // Create Model
    Model *model = new Model;

    // Create Main Screen
    DashboardScreenPresenter *dashboardScreenPresenter = new DashboardScreenPresenter;
    DashboardScreenView *dashboardScreenView = new DashboardScreenView;

    // Create Setup Screen
    SetupScreenPresenter *setupScreenPresenter = new SetupScreenPresenter;
    SetupScreenView *setupScreenView = new SetupScreenView;

    router::Router::getInstance().setCanvas(mvpcanvas);

    router::Router::getInstance().makeScreenRoute("DashboardScreen", dashboardScreenPresenter, dashboardScreenView, model);
    router::Router::getInstance().makeScreenRoute("SetupScreen", setupScreenPresenter, setupScreenView, model);
    router::Router::getInstance().setDefaultScreen("DashboardScreen");

    setupNavigatePanel(navigatePanel);

    router::Router::getInstance().exec();

    return app.exec();
}

void setupNavigatePanel(NavigatePanel *pnavigatePanel)
{
    pnavigatePanel->setHomeLinkAction([]() {
        router::Router::getInstance().makeRedirection("DashboardScreen");
    });

    pnavigatePanel->setSettingsLinkAction([]() {
        router::Router::getInstance().makeRedirection("SetupScreen");
    });

    pnavigatePanel->setActiveLink(NavigatePanel::NavigateLinkList::HomeScreen);
}

void setupAppStyle(QApplication *papp, const QString stylePath)
{

    QFile file(stylePath);
    file.open(QFile::ReadOnly | QFile::Text);

    if (file.exists()) {
        QTextStream stylesheet(&file);
        papp->setStyleSheet(stylesheet.readAll());
    }
}
