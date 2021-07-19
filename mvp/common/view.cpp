#include "mvp/common/view.h"

ViewBase::ViewBase()
{

}

ViewBase::~ViewBase()
{

}

void ViewBase::bind(PresenterBase *presenter)
{
    _presenter = presenter;
}
