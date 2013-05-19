#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewObserver.h"
#include "AbstractEWMainFramePres.h"

class AbstractEWPresenter;
class AbstractEWMainFrame;
class AbstractMsgHandler;
class AbstractOptionsDialogPres;
class EWMainFramePres : public AbstractEWMainFramePres, public EWViewObserver
{
    public:
        EWMainFramePres(AbstractEWPresenter* pres, AbstractMsgHandler* msgHandler, AbstractOptionsDialogPres* optPres);
        virtual ~EWMainFramePres();

        virtual void attachFrame(AbstractEWMainFrame* frame);
        virtual void OnStatusUpdate(AbstractEWPresenter* subject);
        virtual void OnTimeUpdate(AbstractEWPresenter* subject);
        virtual void OnQuit(AbstractEWPresenter* subject);

        virtual void OnFrameQuit();
        virtual void OnFrameAbout();
        virtual void OnFrameOptionsButtonClick();
        virtual void OnFramePlayButtonClick();
        virtual void OnFramePauseButtonClick();
        virtual void OnFrameClose();
    protected:
    private:
        AbstractEWPresenter* m_Presenter;
        AbstractEWMainFrame* m_Frame;
        AbstractMsgHandler* m_MsgHandler;
        AbstractOptionsDialogPres* m_OptionsPres;
};

#endif // EWMAINFRAMEPRES_H
