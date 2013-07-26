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


#include "aweye/core/AbstractTKController.h"
#include "aweye/core/AbstractMsgHandler.h"
#include "aweye/core/BaseException.h"
#include "aweye/core/EventHandler.h"

namespace Aweye {

EventHandler::EventHandler(AbstractMsgHandler& msgHandler,
    AbstractTKController& controller, std::function<bool()>& dispCmd) :
    m_MsgHandler(msgHandler), m_TKController(controller), m_DisplayOptionsDialog(dispCmd)
{
    //ctor
}

EventHandler::~EventHandler()
{
    //dtor
}

void EventHandler::forceUpdate()
{
    notify(&EventHandlerObserver::refresh);
}

void EventHandler::OnViewQuit()
{
    m_TKController.quit();
}

void EventHandler::OnViewAbout()
{
}

void EventHandler::OnViewOptionsButtonClick()
{
    try
    {
        m_DisplayOptionsDialog();
    }
    catch (const BaseException& e)
    {
        m_MsgHandler.displayError(e.what());
    }
}

void EventHandler::OnViewStartStop()
{
    m_TKController.toggleStart();
}

void EventHandler::OnViewPauseResume()
{
    m_TKController.togglePause();
}

void EventHandler::OnViewHideRestore()
{
    m_TKController.show(!m_TKController.isShown());
}
}
