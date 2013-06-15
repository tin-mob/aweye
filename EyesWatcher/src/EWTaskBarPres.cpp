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


#include "EWTaskBarPres.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWTaskbar.h"

EWTaskBarPres::EWTaskBarPres(AbstractMsgHandler& msgHandler, AbstractEWPresenter& presenter,
    AbstractCommand& dispCmd) : EWViewPres(msgHandler, presenter, dispCmd), m_LastIcon("")
{
}

EWTaskBarPres::~EWTaskBarPres()
{
}

void EWTaskBarPres::doStatusUpdate()
{
    assert(m_View != nullptr);
    if (m_View == nullptr) return;

    m_View->setPopupMenuCommands(
        m_Presenter.getHideButtonLabel(),
        m_Presenter.getStartButtonLabel(),
        m_Presenter.getPauseButtonLabel());

    const std::string newIcon = m_Presenter.getIconName();
    if (newIcon != m_LastIcon)
    {
        m_LastIcon = newIcon;
        m_View->setIcon(m_LastIcon);
    }
}

void EWTaskBarPres::doTimeUpdate()
{
    assert(m_View != nullptr);
    if (m_View == nullptr) return;

    m_View->setPopupMenuTimes(
        "Last Session : " + m_Presenter.getTimeOn(),
        "Last Pause : " + m_Presenter.getTimeOff(),
        "Running : " + m_Presenter.getTimeRunning(),
        "Time Left : " + m_Presenter.getTimeLeft());

    const std::string newIcon = m_Presenter.getIconName();
    if (newIcon != m_LastIcon)
    {
        m_LastIcon = newIcon;
        m_View->setIcon(m_LastIcon);
    }
}

void EWTaskBarPres::doQuit()
{
    assert(m_View != nullptr);
    if (m_View == nullptr) return;

    m_View->setIcon("");
}
