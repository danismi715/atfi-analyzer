#ifndef SETUPSCREENVIEW_H
#define SETUPSCREENVIEW_H

#include <QMainWindow>
#include "mvp/common/view.h"
#include "mvp/gui/presenter/setupscreen/setupscreenpresenter.h"

class SetupScreenView : public QMainWindow, public ViewBase
{
    Q_OBJECT

public:
    explicit SetupScreenView(QWidget *parent = nullptr);
    ~SetupScreenView();

    void show() override;
    void update() override;
    void exit() override;

private:
};

#endif // SETUPSCREENVIEW_H
