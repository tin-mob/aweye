/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "aweye/core/AbstractEventHandler.h"
#include "aweye/core/AbstractMainFrame.h"
#include "aweye/core/AbstractTKController.h"
#include "aweye/core/MainFramePres.h"

namespace Aweye {

MainFramePres::MainFramePres(AbstractMainFrame& frame, AbstractTKController& controller,
                                 AbstractEventHandler& hdlr) :
    m_Frame(frame), m_TKController(controller), m_EventHandler(hdlr)
{
    m_TKController.attach(this);
    m_EventHandler.attach(this);

    refresh();
}

MainFramePres::~MainFramePres()
{
    m_TKController.detach(this);
    m_EventHandler.detach(this);
}

void MainFramePres::OnStatusUpdate()
{
    const bool shown = m_TKController.isShown();
    m_Frame.show(shown);
    if (shown)
    {
        m_Frame.setPauseButtonLabel(m_TKController.getPauseButtonLabel());
        m_Frame.setStartButtonLabel(m_TKController.getStartButtonLabel());

        // times could change in a status update (stop)
        m_Frame.setValues(m_TKController.getStatus(), m_TKController.getTimeOn(),
            m_TKController.getTimeOff(), m_TKController.getTimeRunning(),
            m_TKController.getTimeLeft());
    }
}

void MainFramePres::OnTimeUpdate()
{
    if (m_TKController.isShown())
    {
        m_Frame.setValues(m_TKController.getStatus(), m_TKController.getTimeOn(),
            m_TKController.getTimeOff(), m_TKController.getTimeRunning(),
            m_TKController.getTimeLeft());
    }
}

void MainFramePres::OnQuit()
{
    m_Frame.close();
}

void MainFramePres::refresh()
{
    OnStatusUpdate();
}
}
