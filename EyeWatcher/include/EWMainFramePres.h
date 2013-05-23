#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewPres.h"

class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractEWMainFrame;
class EWMainFramePres : public EWViewPres<AbstractEWMainFrame>
{
    public:
        EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWMainFramePres();
    protected:
        virtual void doStatusUpdate();
        virtual void doTimeUpdate();
        virtual void doQuit();
    private:

        AbstractEWMainFrame* m_Frame;
};

#endif // EWMAINFRAMEPRES_H
