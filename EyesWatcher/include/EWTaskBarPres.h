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


#ifndef EWTASKBARPRES_H
#define EWTASKBARPRES_H

#include "AbstractEventHandler.h"
#include "EWViewObserver.h"
#include <string>

namespace EW
{
class AbstractEventHandler;
class AbstractEWPresenter;
class AbstractEWTaskbar;
class EWTaskBarPres : public EWViewObserver, public EventHandlerObserver
{
    public:
        EWTaskBarPres(AbstractEWTaskbar& taskBar, AbstractEWPresenter& presenter,
                      AbstractEventHandler& hdlr);
        virtual ~EWTaskBarPres();

        virtual void OnStatusUpdate();
        virtual void OnTimeUpdate();
        virtual void OnQuit();
        virtual void refresh();
    protected:
    private:
        void setIcon();

        AbstractEWTaskbar& m_TaskBar;
        AbstractEWPresenter& m_Presenter;
        AbstractEventHandler& m_EventHandler;
        std::string m_LastIcon;
};
}

#endif // EWTASKBARPRES_H
