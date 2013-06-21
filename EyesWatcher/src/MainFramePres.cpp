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

#include "AbstractEventHandler.h"
#include "AbstractMainFrame.h"
#include "AbstractTKController.h"
#include "BaseException.h"
#include "MainFramePres.h"

namespace EW
{
MainFramePres::MainFramePres(AbstractMainFrame& frame, AbstractTKController& presenter,
                                 AbstractEventHandler& hdlr) :
    m_Frame(frame), m_Presenter(presenter), m_EventHandler(hdlr)
{
    m_Presenter.attach(this);
    m_EventHandler.attach(this);

    refresh();
}

MainFramePres::~MainFramePres()
{
    m_Presenter.detach(this);
    m_EventHandler.detach(this);
}

void MainFramePres::OnStatusUpdate()
{
    const bool shown = m_Presenter.isShown();
    m_Frame.show(shown);
    if (shown)
    {
        m_Frame.setPauseButtonLabel(m_Presenter.getPauseButtonLabel());
        m_Frame.setStartButtonLabel(m_Presenter.getStartButtonLabel());

        // times could change in a status update (stop)
        m_Frame.setValues(m_Presenter.getStatus(), m_Presenter.getTimeOn(),
            m_Presenter.getTimeOff(), m_Presenter.getTimeRunning(),
            m_Presenter.getTimeLeft());
    }
}

void MainFramePres::OnTimeUpdate()
{
    if (m_Presenter.isShown())
    {
        m_Frame.setValues(m_Presenter.getStatus(), m_Presenter.getTimeOn(),
            m_Presenter.getTimeOff(), m_Presenter.getTimeRunning(),
            m_Presenter.getTimeLeft());
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
