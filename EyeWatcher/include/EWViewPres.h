/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


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
