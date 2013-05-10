#ifndef OBSERVABLEWXMENU_H
#define OBSERVABLEWXMENU_H

#include "Observer.h"

class ObservableWxMenu : public wxMenu, public Observable
{
    public:
        virtual ~ObservableWxMenu();
    protected:
    private:
};

#endif // OBSERVABLEWXMENU_H
