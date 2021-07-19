#ifndef PRESENTER_H
#define PRESENTER_H

#include <QList>
#include <QObject>
#include "view.h"
#include "mvp/model/model.h"
#include "mvp/common/router.h"

class ViewBase;

class PresenterBase
{
public:
    explicit PresenterBase();
    explicit PresenterBase(Model *model, ViewBase *view);
    virtual ~PresenterBase();

    virtual ViewBase* getView();
    virtual void bindModel(Model *model);
    virtual void bindView(ViewBase *view, int id);
    virtual int getViewId();
    virtual void postbinding();
    virtual void updateView();
    virtual void exec();
    virtual void exit();
protected:
    Model *_model;
    ViewBase *_view;
    int _id;
};

#endif // PRESENTER_H
