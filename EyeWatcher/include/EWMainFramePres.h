#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewPres.h"

class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractEWMainFrame;
class EWMainFramePres : public EWViewPres
{
    public:
        EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWMainFramePres();

        ///@todo: find a way to merge with taskbar so that it can be used in view constructor
        void attachFrame(AbstractEWMainFrame* frame);

    protected:
        virtual void doStatusUpdate();
        virtual void doTimeUpdate();
        virtual void doQuit();
    private:

        AbstractEWMainFrame* m_Frame;
};

#endif // EWMAINFRAMEPRES_H
