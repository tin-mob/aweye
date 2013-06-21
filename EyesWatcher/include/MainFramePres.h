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


#ifndef MAINFRAMEPRES_H
#define MAINFRAMEPRES_H

#include "AbstractEventHandler.h"
#include "TKControllerObserver.h"

namespace EW
{
class AbstractEventHandler;
class AbstractMainFrame;
class AbstractTKController;
class MainFramePres : public TKControllerObserver, public EventHandlerObserver
{
    public:
        MainFramePres(AbstractMainFrame& frame, AbstractTKController& presenter,
                        AbstractEventHandler& hdlr);
        virtual ~MainFramePres();

        virtual void OnStatusUpdate();
        virtual void OnTimeUpdate();
        virtual void OnQuit();
        virtual void refresh();
    protected:
    private:
        AbstractMainFrame& m_Frame;
        AbstractTKController& m_Presenter;
        AbstractEventHandler& m_EventHandler;
};
}

#endif // MAINFRAMEPRES_H
