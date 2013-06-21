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


#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "AbstractEventHandler.h"
#include <functional>

namespace EW
{
class AbstractTKController;
class AbstractMsgHandler;
class EventHandler : public AbstractEventHandler
{
    public:
        EventHandler(AbstractMsgHandler& msgHandler, AbstractTKController& presenter,
                     std::function<bool()>& dispCmd);
        virtual ~EventHandler();

        virtual void forceUpdate();
        virtual void OnViewQuit();
        virtual void OnViewAbout();
        virtual void OnViewOptionsButtonClick();
        virtual void OnViewStartStop();
        virtual void OnViewPauseResume();
        virtual void OnViewHideRestore();
    protected:
    private:
        AbstractMsgHandler& m_MsgHandler;
        AbstractTKController& m_Presenter;
        std::function<bool()>& m_DisplayOptionsDialog;
};
}

#endif // EVENTHANDLER_H
