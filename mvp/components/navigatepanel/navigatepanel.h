#ifndef NAVIGATEPANEL_H
#define NAVIGATEPANEL_H

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QPalette>
#include <QColor>
#include <QAbstractButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QDebug>
#include <functional>
#include <array>

class NavigatePanel : public QWidget
{
    Q_OBJECT
public:
    enum PanelOrientation {
        Horizontal,
        Vertical
    };

    enum NavigateLinkList {
        HomeScreen,
        SetupScreen,
        LinkNumber
    };

    NavigatePanel(QWidget *parent);
    NavigatePanel(PanelOrientation orientation, QWidget *parent);

    void setHomeLinkAction(std::function<void(void)> &&action);
    void setSettingsLinkAction(std::function<void(void)> &&action);
    void setActiveLink(NavigateLinkList link);
    void paintEvent(QPaintEvent *pe) override;
public slots:
    void onClickedToHomeScreen();
    void onClickToSettingsScreen();

signals:

private:
    static const int WIDGET_SIZE = 60;

    PanelOrientation _orientation;
    std::array<QRadioButton*, LinkNumber> _navigate_btn_list;
    std::function<void(void)> _home_button_action;
    std::function<void(void)> _settings_button_action;
};

#endif // NAVIGATEPANEL_H
