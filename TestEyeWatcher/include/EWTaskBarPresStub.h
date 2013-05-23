#ifndef EWTASKBARPRESSTUB_H
#define EWTASKBARPRESSTUB_H

#include "AbstractEWViewPres.h"
#include "AbstractEWTaskbar.h"

class EWTaskBarPresStub : public AbstractEWViewPres<AbstractEWTaskbar>
{
    public:
        EWTaskBarPresStub(AbstractEWPresenter* p, AbstractEWAppController* c) :
            presenter(p), controller(c) {}
        virtual ~EWTaskBarPresStub() {}

        virtual void forceUpdate() {}
        virtual void OnViewQuit() {}
        virtual void OnViewAbout() {}
        virtual void OnViewOptionsButtonClick() {}
        virtual void OnViewStartStop() {}
        virtual void OnViewPauseResume() {}
        virtual void OnViewHideRestore() {}

        AbstractEWPresenter* presenter;
        AbstractEWAppController* controller;
    protected:
    private:
};

#endif // EWTASKBARPRESSTUB_H
