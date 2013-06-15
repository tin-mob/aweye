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

#include "AbstractEWMainFrame.h"
#include "AbstractEWPresenter.h"
#include "BaseException.h"
#include "EWMainFramePres.h"

EWMainFramePres::EWMainFramePres(AbstractMsgHandler& msgHandler, AbstractEWPresenter& presenter,
    AbstractCommand& dispCmd) : EWViewPres(msgHandler, presenter, dispCmd)
{
}

EWMainFramePres::~EWMainFramePres()
{
}

void EWMainFramePres::doStatusUpdate()
{
    assert(m_View != nullptr);
    if (m_View == nullptr) return;

    const bool shown = m_Presenter.isShown();
    m_View->show(shown);
    if (shown)
    {
        m_View->setPauseButtonLabel(m_Presenter.getPauseButtonLabel());
        m_View->setStartButtonLabel(m_Presenter.getStartButtonLabel());

        // times could change in a status update (stop)
        m_View->setValues(m_Presenter.getStatus(), m_Presenter.getTimeOn(),
            m_Presenter.getTimeOff(), m_Presenter.getTimeRunning(),
            m_Presenter.getTimeLeft());
    }
}

void EWMainFramePres::doTimeUpdate()
{
    assert(m_View != nullptr);
    if (m_View == nullptr) return;

    if (m_Presenter.isShown())
    {
        m_View->setValues(m_Presenter.getStatus(), m_Presenter.getTimeOn(),
            m_Presenter.getTimeOff(), m_Presenter.getTimeRunning(),
            m_Presenter.getTimeLeft());
    }
}

void EWMainFramePres::doQuit()
{
    m_View->close();
}
