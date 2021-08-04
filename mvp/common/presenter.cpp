#include "mvp/common/presenter.h"

PresenterBase::PresenterBase()
{
}

PresenterBase::PresenterBase(Model *model, ViewBase *view)
    : _model(model)
    , _view(view)
{
}

void PresenterBase::bindModel(Model *model)
{
    _model = model;
}

int PresenterBase::getViewId()
{
    return _id;
}

void PresenterBase::bindView(ViewBase *view, int id)
{
    _id = id;
    _view = view;
    _view->bind(this);
    postbinding();
}

void PresenterBase::postbinding()
{
    //This method should be overided
    //Here user should connect signals and slots in order to receive event from view
}

void PresenterBase::updateView()
{
    _view->update();
}

PresenterBase::~PresenterBase()
{
    delete _model;
    delete _view;
}

ViewBase* PresenterBase::getView()
{
    return _view;
}

void PresenterBase::exec()
{
}

void PresenterBase::exit()
{
    _view->exit();
}
