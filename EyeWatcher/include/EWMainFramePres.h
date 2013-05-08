#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "Observer.h"

class EWPresenter;
class AbstractEWMainFrame;
class AbstractMsgHandler;
class OptionsDialogPres;
class EWMainFramePres : public Observer
{
    public:
        EWMainFramePres(EWPresenter* pres, AbstractMsgHandler* msgHandler, OptionsDialogPres* optPres);
        virtual ~EWMainFramePres();

        virtual void attachFrame(AbstractEWMainFrame* frame);
        virtual void update(Observable*);

        void OnQuit();
        void OnAbout();
        void OnOptionsButtonClick();
        void OnPlayButtonClick();
        void OnPauseButtonClick();
        void OnClose();
    protected:
    private:
        EWPresenter* m_Presenter;
        AbstractEWMainFrame* m_Frame;
        AbstractMsgHandler* m_MsgHandler;
        OptionsDialogPres* m_OptionsPres;
};

#endif // EWMAINFRAMEPRES_H
