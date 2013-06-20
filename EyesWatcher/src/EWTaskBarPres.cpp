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
#include "AbstractEventHandler.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWTaskbar.h"

namespace EW
{
EWTaskBarPres::EWTaskBarPres(AbstractEWTaskbar& taskBar, AbstractEWPresenter& presenter,
                             AbstractEventHandler& hdlr) :
    m_TaskBar(taskBar), m_Presenter(presenter), m_EventHandler(hdlr), m_LastIcon("")
{
    m_Presenter.attach(this);
    m_EventHandler.attach(this);

    refresh();
}

EWTaskBarPres::~EWTaskBarPres()
{
    m_Presenter.detach(this);
    m_EventHandler.detach(this);
}

void EWTaskBarPres::OnStatusUpdate()
{
    m_TaskBar.setPopupMenuCommands(
        m_Presenter.getHideButtonLabel(),
        m_Presenter.getStartButtonLabel(),
        m_Presenter.getPauseButtonLabel());
    setIcon();
}

void EWTaskBarPres::OnTimeUpdate()
{
    m_TaskBar.setPopupMenuTimes(
        "Last Session : " + m_Presenter.getTimeOn(),
        "Last Pause : " + m_Presenter.getTimeOff(),
        "Running : " + m_Presenter.getTimeRunning(),
        "Time Left : " + m_Presenter.getTimeLeft());
    setIcon();
}

void EWTaskBarPres::OnQuit()
{
    m_TaskBar.setIcon("");
}

void EWTaskBarPres::setIcon()
{
    const std::string newIcon = m_Presenter.getIconName();
    if (newIcon != m_LastIcon)
    {
        m_LastIcon = newIcon;
        m_TaskBar.setIcon(m_LastIcon);
    }
}

void EWTaskBarPres::refresh()
{
    OnStatusUpdate();
    OnTimeUpdate();
}
}
