#ifndef OBSERVABLEWXMENU_H
#define OBSERVABLEWXMENU_H

#include "Subject.h"
#include <wx/menu.h>

class ObservableWxMenuObserver;
class ObservableWxMenu : public wxMenu, public Subject<ObservableWxMenuObserver, ObservableWxMenu*>
{
    public:
        virtual ~ObservableWxMenu();
    protected:
    private:
};

class ObservableWxMenuObserver  // yeah!
{
    public:
        virtual ~ObservableWxMenuObserver() {}
        virtual void onMenuDelete(ObservableWxMenu* menu) = 0;
};

#endif // OBSERVABLEWXMENU_H
