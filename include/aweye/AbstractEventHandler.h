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


#ifndef ABSTRACTEVENTHANDLER_H
#define ABSTRACTEVENTHANDLER_H

#include "aweye/Subject.h"

namespace Aweye {

class EventHandlerObserver
{
    public:
        virtual ~EventHandlerObserver() {}
        virtual void refresh() = 0;
};

class AbstractEventHandler : public Subject<EventHandlerObserver>
{
    public:
        virtual ~AbstractEventHandler() {}
        virtual void forceUpdate() = 0;
        virtual void OnViewQuit() = 0;
        virtual void OnViewAbout() = 0;
        virtual void OnViewOptionsButtonClick() = 0;
        virtual void OnViewStartStop() = 0;
        virtual void OnViewPauseResume() = 0;
        virtual void OnViewHideRestore() = 0;
    protected:
    private:
};
}

#endif // ABSTRACTEVENTHANDLER_H
