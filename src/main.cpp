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

void setupNavigatePanel(NavigatePanel *pnavigatePanel);
void setupAppStyle(QApplication *papp, const QString stylePath);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setupAppStyle(&app, ":/style.qss");

    NavigatePanel *navigate_panel = new NavigatePanel(NavigatePanel::Horizontal, nullptr);
    MVPCanvas *mvp_canvas = new MVPCanvas(640, 480);

    mvp_canvas->addNavigatePanel(Qt::DockWidgetArea::BottomDockWidgetArea, navigate_panel);

    // Create Model
    Model *model = new Model;

    // Create Main Screen
    DashboardScreenPresenter *dashboard_screen_presenter = new DashboardScreenPresenter;
    DashboardScreenView *dashboard_screen_view = new DashboardScreenView;

    // Create Setup Screen
    SetupScreenPresenter *setup_screen_presenter = new SetupScreenPresenter;
    SetupScreenView *setup_screen_view = new SetupScreenView;

    router::Router::getInstance().setCanvas(mvp_canvas);

    router::Router::getInstance().makeScreenRoute("DashboardScreen", dashboard_screen_presenter, dashboard_screen_view, model);
    router::Router::getInstance().makeScreenRoute("SetupScreen", setup_screen_presenter, setup_screen_view, model);
    router::Router::getInstance().setDefaultScreen("DashboardScreen");

    setupNavigatePanel(navigate_panel);

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
