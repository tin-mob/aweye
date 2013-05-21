#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewObserver.h"
#include "AbstractEWMainFramePres.h"

class AbstractEWPresenter;
class AbstractEWMainFrame;
class AbstractMsgHandler;
class AbstractOptionsDialogPres;
class AbstractEWAppController;
class EWMainFramePres : public AbstractEWMainFramePres, public EWViewObserver
{
    public:
        EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWMainFramePres();

        virtual void attachFrame(AbstractEWMainFrame* frame);
        virtual void OnStatusUpdate(AbstractEWPresenter*);
        virtual void OnTimeUpdate(AbstractEWPresenter*);
        virtual void OnQuit(AbstractEWPresenter*);

        virtual void OnFrameQuit();
        virtual void OnFrameAbout();
        virtual void OnFrameOptionsButtonClick();
        virtual void OnFramePlayButtonClick();
        virtual void OnFramePauseButtonClick();
        virtual void OnFrameClose();
    protected:
    private:
        void doStatusUpdate();
        void doTimeUpdate();
        void doQuit();

        AbstractEWPresenter* m_Presenter;
        AbstractEWMainFrame* m_Frame;
        AbstractEWAppController* m_Controller;
};

#endif // EWMAINFRAMEPRES_H
