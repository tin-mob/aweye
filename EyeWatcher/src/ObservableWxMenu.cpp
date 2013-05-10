#include "ObservableWxMenu.h"

ObservableWxMenu::~ObservableWxMenu()
{
    //dtor
    notify();
}
