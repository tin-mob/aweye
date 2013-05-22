#ifndef EWVIEWPRES_H
#define EWVIEWPRES_H

#include "EWViewObserver.h"
#include "AbstractEWViewPres.h"

class AbstractEWPresenter;
class AbstractEWAppController;
class EWViewPres : public EWViewObserver, public AbstractEWViewPres
{
    public:
        EWViewPres(AbstractEWPresenter* presenter, AbstractEWAppController* controller);
        virtual ~EWViewPres();

        virtual void OnStatusUpdate(AbstractEWPresenter*);
        virtual void OnTimeUpdate(AbstractEWPresenter*);
        virtual void OnQuit(AbstractEWPresenter*);

        virtual void forceUpdate();
        virtual void OnViewQuit();
        virtual void OnViewAbout();
        virtual void OnViewOptionsButtonClick();
        virtual void OnViewStartStop();
        virtual void OnViewPauseResume();
        virtual void OnViewHideRestore();

    protected:
        virtual void doStatusUpdate() = 0;
        virtual void doTimeUpdate() = 0;
        virtual void doQuit() = 0;

        AbstractEWPresenter* m_Presenter;
        AbstractEWAppController* m_Controller;
    private:
};

#endif // EWVIEWPRES_H
