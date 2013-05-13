#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewObserver.h"

class EWPresenter;
class AbstractEWMainFrame;
class AbstractMsgHandler;
class OptionsDialogPres;
class EWMainFramePres : public EWViewObserver
{
    public:
        EWMainFramePres(EWPresenter* pres, AbstractMsgHandler* msgHandler, OptionsDialogPres* optPres);
        virtual ~EWMainFramePres();

        virtual void attachFrame(AbstractEWMainFrame* frame);
        virtual void OnStatusUpdate();
        virtual void OnTimeUpdate();
        virtual void OnQuit();

        void OnFrameQuit();
        void OnFrameAbout();
        void OnFrameOptionsButtonClick();
        void OnFramePlayButtonClick();
        void OnFramePauseButtonClick();
        void OnFrameClose();
    protected:
    private:
        EWPresenter* m_Presenter;
        AbstractEWMainFrame* m_Frame;
        AbstractMsgHandler* m_MsgHandler;
        OptionsDialogPres* m_OptionsPres;
};

#endif // EWMAINFRAMEPRES_H
