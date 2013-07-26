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


#ifndef EVENTHANDLERSTUB_H
#define EVENTHANDLERSTUB_H

#include "aweye/core/AbstractEventHandler.h"
#include "aweye/core/AbstractMsgHandler.h"
#include "aweye/core/AbstractTKController.h"

#include <functional>

namespace Aweye
{
class EventHandlerObserverStub : public EventHandlerObserver
{
    public:
        EventHandlerObserverStub(AbstractEventHandler& hdlr) :
            m_Refreshed(false), m_EventHandler(hdlr)
        {
            m_EventHandler.attach(this);
        }
        virtual ~EventHandlerObserverStub()
        {
            m_EventHandler.detach(this);
        }
        virtual void refresh() {m_Refreshed = true;}

        bool m_Refreshed;
        AbstractEventHandler& m_EventHandler;
};

class EventHandlerStub : public AbstractEventHandler
{
    public:
        EventHandlerStub(AbstractMsgHandler& msgHandler, AbstractTKController& controller,
            std::function<bool()>& dispCmd)
            : m_MsgHandler(&msgHandler), m_TKController(&controller), m_DisplayOptionsDialog(&dispCmd){}

        EventHandlerStub() : m_MsgHandler(nullptr), m_TKController(nullptr),
            m_DisplayOptionsDialog(nullptr) {}
        virtual ~EventHandlerStub() {}

        virtual void forceUpdate() {notify(&EventHandlerObserver::refresh);}
        virtual void OnViewQuit() {}
        virtual void OnViewAbout() {}
        virtual void OnViewOptionsButtonClick() {}
        virtual void OnViewStartStop() {}
        virtual void OnViewPauseResume() {}
        virtual void OnViewHideRestore() {}

        AbstractMsgHandler* m_MsgHandler;
        AbstractTKController* m_TKController;
        std::function<bool()>* m_DisplayOptionsDialog;
    protected:
    private:
};
}

#endif // EVENTHANDLERSTUB_H
