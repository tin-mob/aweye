/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/

/// @todo not certain about current inheritance structure...

#ifndef EWVIEWPRES_H
#define EWVIEWPRES_H

#include "AbstractCommand.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWViewPres.h"
#include "AbstractMsgHandler.h"
#include "BaseException.h"
#include "EWViewObserver.h"

template <class TView>
class EWViewPres : public EWViewObserver, public AbstractEWViewPres<TView>
{
    public:
        EWViewPres(AbstractMsgHandler& msgHandler, AbstractEWPresenter& presenter, AbstractCommand& dispCmd) :
            m_MsgHandler(msgHandler), m_Presenter(presenter), m_DisplayOptionsDialog(dispCmd)
        {
            m_Presenter.attach(this);
        }

        virtual ~EWViewPres()
        {
            m_Presenter.detach(this);
        }

        virtual void OnStatusUpdate(AbstractEWPresenter*)
        {
            doStatusUpdate();
        }

        virtual void OnTimeUpdate(AbstractEWPresenter*)
        {
            doTimeUpdate();
        }

        virtual void OnQuit(AbstractEWPresenter*)
        {
            doQuit();
        }

        virtual void forceUpdate()
        {
            doStatusUpdate();
            doTimeUpdate();
        }

        virtual void OnViewQuit()
        {
            m_Presenter.quit();
        }

        virtual void OnViewAbout()
        {
        }

        virtual void OnViewOptionsButtonClick()
        {
            try
            {
                m_DisplayOptionsDialog.execute();
            }
            catch (BaseException e)
            {
                m_MsgHandler.displayError(e.what());
            }
        }

        virtual void OnViewStartStop()
        {
            m_Presenter.toggleStart();
        }

        virtual void OnViewPauseResume()
        {
            m_Presenter.togglePause();
        }

        virtual void OnViewHideRestore()
        {
            m_Presenter.show(!m_Presenter.isShown());
        }

    protected:
        virtual void doStatusUpdate() = 0;
        virtual void doTimeUpdate() = 0;
        virtual void doQuit() = 0;

        AbstractMsgHandler& m_MsgHandler;
        AbstractEWPresenter& m_Presenter;
        AbstractCommand& m_DisplayOptionsDialog;
    private:
};

#endif // EWVIEWPRES_H
