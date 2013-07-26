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

#ifndef VIEWPRESSTUB_H
#define VIEWPRESSTUB_H

#include "aweye/core/AbstractEventHandler.h"
#include "aweye/core/TKControllerObserver.h"

namespace Aweye
{
class AbstractEventHandler;
class AbstractMainFrame;
class AbstractTKController;

///@note separate when needed
template <class TView>
class ViewPresStub : public TKControllerObserver, public EventHandlerObserver
{
    public:
        ViewPresStub(TView& view, AbstractTKController& controller,
            AbstractEventHandler& hdlr) :
            m_View(&view), m_TKController(&controller), m_EventHandler(&hdlr) {}
        virtual ~ViewPresStub() {}

        virtual void OnStatusUpdate() {}
        virtual void OnTimeUpdate() {}
        virtual void OnQuit() {}
        virtual void refresh() {}

        TView* m_View;
        AbstractTKController* m_TKController;
        AbstractEventHandler* m_EventHandler;
    protected:
    private:
};
}

#endif // VIEWPRESSTUB_H
