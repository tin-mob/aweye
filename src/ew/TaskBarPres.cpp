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


#include "ew/AbstractEventHandler.h"
#include "ew/AbstractTaskBar.h"
#include "ew/AbstractTKController.h"
#include "ew/TaskBarPres.h"
#include "ew/tr.h"

namespace EW {

TaskBarPres::TaskBarPres(AbstractTaskBar& taskBar, AbstractTKController& controller,
                             AbstractEventHandler& hdlr) :
    m_TaskBar(taskBar), m_TKController(controller), m_EventHandler(hdlr), m_LastIcon("")
{
    m_TKController.attach(this);
    m_EventHandler.attach(this);

    refresh();
}

TaskBarPres::~TaskBarPres()
{
    m_TKController.detach(this);
    m_EventHandler.detach(this);
}

void TaskBarPres::OnStatusUpdate()
{
    m_TaskBar.setPopupMenuCommands(
        m_TKController.getHideButtonLabel(),
        m_TKController.getStartButtonLabel(),
        m_TKController.getPauseButtonLabel());
    setIcon();
}

void TaskBarPres::OnTimeUpdate()
{
    m_TaskBar.setPopupMenuTimes(
        tr("Last Session : ") + m_TKController.getTimeOn(),
        tr("Last Pause : ") + m_TKController.getTimeOff(),
        tr("Running : ") + m_TKController.getTimeRunning(),
        tr("Time Left : ") + m_TKController.getTimeLeft());
    setIcon();
}

void TaskBarPres::OnQuit()
{
    m_TaskBar.setIcon("");
}

void TaskBarPres::setIcon()
{
    const std::string newIcon = m_TKController.getIconName();
    if (newIcon != m_LastIcon)
    {
        m_LastIcon = newIcon;
        m_TaskBar.setIcon(m_LastIcon);
    }
}

void TaskBarPres::refresh()
{
    OnStatusUpdate();
    OnTimeUpdate();
}
}
