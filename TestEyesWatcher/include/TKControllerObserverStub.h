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


#ifndef OBSERVERSTUB_H
#define OBSERVERSTUB_H

#include "TKControllerObserver.h"

namespace EW
{
class TKControllerObserverStub : public TKControllerObserver
{
    public:
        TKControllerObserverStub() : m_StatUpdated(false), m_TimeUpdated(false), m_QuitUpdated(false){}
        virtual ~TKControllerObserverStub() {}
        virtual void OnStatusUpdate() {m_StatUpdated = true;}
        virtual void OnTimeUpdate() {m_TimeUpdated = true;}
        virtual void OnQuit() {m_QuitUpdated = true;}
        bool checkStatUpdated() {bool temp = m_StatUpdated; m_StatUpdated = false; return temp;}
        bool checkTimeUpdated() {bool temp = m_TimeUpdated; m_TimeUpdated = false; return temp;}
        bool checkQuitUpdated() {bool temp = m_QuitUpdated; m_QuitUpdated = false; return temp;}
    protected:
    private:
        bool m_StatUpdated;
        bool m_TimeUpdated;
        bool m_QuitUpdated;
};
}

#endif // OBSERVERSTUB_H
