#ifndef EWVIEWPRES_H
#define EWVIEWPRES_H

#include "EWViewObserver.h"
#include "AbstractEWViewPres.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWAppController.h"

template <class TView>
class EWViewPres : public EWViewObserver, public AbstractEWViewPres<TView>
{
    public:
        EWViewPres(AbstractEWPresenter* presenter, AbstractEWAppController* controller) :
            m_Presenter(presenter), m_Controller(controller)
        {
            assert(presenter);
            assert(controller);
            this->m_Presenter->attach(this);
        }

        virtual ~EWViewPres()
        {
            this->m_Presenter->detach(this);
        }

        virtual void OnStatusUpdate(AbstractEWPresenter*)
        {
            this->doStatusUpdate();
        }

        virtual void OnTimeUpdate(AbstractEWPresenter*)
        {
            this->doTimeUpdate();
        }

        virtual void OnQuit(AbstractEWPresenter*)
        {
            this->doQuit();
        }

        virtual void forceUpdate()
        {
            this->doStatusUpdate();
            this->doTimeUpdate();
        }

        virtual void OnViewQuit()
        {
            this->m_Presenter->quit();
        }

        virtual void OnViewAbout()
        {
        }

        virtual void OnViewOptionsButtonClick()
        {
            this->m_Controller->displayOptionsDialog();
        }

        virtual void OnViewStartStop()
        {
            this->m_Presenter->toggleStart();
        }

        virtual void OnViewPauseResume()
        {
            this->m_Presenter->togglePause();
        }

        virtual void OnViewHideRestore()
        {
            this->m_Presenter->show(!this->m_Presenter->isShown());
        }

    protected:
        virtual void doStatusUpdate() = 0;
        virtual void doTimeUpdate() = 0;
        virtual void doQuit() = 0;

        AbstractEWPresenter* m_Presenter;
        AbstractEWAppController* m_Controller;
    private:
};

#endif // EWVIEWPRES_H
