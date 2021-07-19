#ifndef SETUPSCREENPRESENTER_H
#define SETUPSCREENPRESENTER_H

#include "mvp/common/presenter.h"
#include "mvp/gui/view/setupscreen/setupscreenview.h"

class SetupScreenView;

class SetupScreenPresenter : public QObject, public PresenterBase
{
    Q_OBJECT

public:
    SetupScreenPresenter();
    void postbinding() override;
};

#endif // SETUPSCREENPRESENTER_H
