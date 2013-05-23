#ifndef EWMAINFRAMEPRESSTUB_H
#define EWMAINFRAMEPRESSTUB_H

#include "AbstractEWViewPres.h"
#include "AbstractEWMainFrame.h"

class EWMainFramePresStub : public AbstractEWViewPres<AbstractEWMainFrame>
{
    public:
        EWMainFramePresStub(AbstractEWPresenter* p, AbstractEWAppController* c) :
            presenter(p), controller(c) {}
        virtual ~EWMainFramePresStub() {}

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

#endif // EWMAINFRAMEPRESSTUB_H
