#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "Observer.h"

class EWPresenter;
class AbstractEWMainFrame;
class AbstractMsgHandler;
class EWMainFramePres : public Observer
{
    public:
        EWMainFramePres(EWPresenter* pres, AbstractMsgHandler* msgHandler);
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
};

#endif // EWMAINFRAMEPRES_H
