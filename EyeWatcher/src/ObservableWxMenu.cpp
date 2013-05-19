#include "ObservableWxMenu.h"

ObservableWxMenu::~ObservableWxMenu()
{
    //dtor
    notify(&ObservableWxMenuObserver::onMenuDelete, this);
}
