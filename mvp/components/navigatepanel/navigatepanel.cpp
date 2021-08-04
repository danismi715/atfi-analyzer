#include "navigatepanel.h"
#include "mvp/common/router.h"
#include <QStyleOption>
#include <QPainter>

NavigatePanel::NavigatePanel(QWidget *parent)
    : NavigatePanel(NavigatePanel::PanelOrientation ::Vertical, parent)
{
}

NavigatePanel::NavigatePanel(NavigatePanel::PanelOrientation orientation, QWidget *parent)
    : QWidget(parent)
    , _orientation(orientation)
{
    // Set size for navigate panel
    _orientation == PanelOrientation::Vertical
            ? setFixedWidth(WIDGET_SIZE)
            : setFixedHeight(WIDGET_SIZE);

    // Set color scheme

    // Create buttons
    _navigate_btn_list[NavigateLinkList::HomeScreen] = new QRadioButton(this);
    _navigate_btn_list[NavigateLinkList::SetupScreen] = new QRadioButton(this);

    _navigate_btn_list[NavigateLinkList::HomeScreen]->setObjectName("homeButton");
    _navigate_btn_list[NavigateLinkList::SetupScreen]->setObjectName("settingsButton");

    // Create layout to navigate panel
    QBoxLayout *layout = _orientation == PanelOrientation::Vertical
            ? (QBoxLayout*)new QVBoxLayout(this)
            : (QBoxLayout*)new QHBoxLayout(this);

    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    for (auto &i : _navigate_btn_list) {
        i->setMinimumSize(QSize(WIDGET_SIZE / 2, WIDGET_SIZE / 2));
        i->setMaximumSize(QSize(WIDGET_SIZE, WIDGET_SIZE));
        i->setCheckable(true);
        layout->addWidget(i);
    }

    // Set policy
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Connect button's click events to navigate panel slots
    connect(_navigate_btn_list[NavigateLinkList::HomeScreen], SIGNAL(clicked()), this, SLOT(onClickedToHomeScreen()));
    connect(_navigate_btn_list[NavigateLinkList::SetupScreen], SIGNAL(clicked()), this, SLOT(onClickToSettingsScreen()));
}

void NavigatePanel::setHomeLinkAction(std::function<void ()> &&action)
{
    _home_button_action = action;
}

void NavigatePanel::setSettingsLinkAction(std::function<void ()> &&action)
{
    _settings_button_action = action;
}

void NavigatePanel::setActiveLink(NavigatePanel::NavigateLinkList link)
{
    _navigate_btn_list[link]->setChecked(true);
}

void NavigatePanel::onClickedToHomeScreen()
{
    _home_button_action();
}

void NavigatePanel::onClickToSettingsScreen()
{
    _settings_button_action();
}

void NavigatePanel::paintEvent(QPaintEvent *pe) {
    (void)pe;
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
};


