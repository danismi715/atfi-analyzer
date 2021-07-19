#ifndef VIEWBASE_H
#define VIEWBASE_H

#include <QWidget>
#include "presenter.h"

class PresenterBase;

class ViewBase
{
public:
    explicit ViewBase();
    virtual ~ViewBase();

    virtual void show() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;

    void bind(PresenterBase *presenter);
protected:
    PresenterBase *_presenter;
};

#endif // VIEWBASE_H
