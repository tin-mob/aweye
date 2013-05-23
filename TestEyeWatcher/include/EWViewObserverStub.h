/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef OBSERVERSTUB_H
#define OBSERVERSTUB_H

#include "EWViewObserver.h"

class EWViewObserverStub : public EWViewObserver
{
    public:
        EWViewObserverStub() : statUpdated(false), timeUpdated(false), quitUpdated(false){}
        virtual ~EWViewObserverStub() {}
        virtual void OnStatusUpdate(AbstractEWPresenter* subject) {statUpdated = true;}
        virtual void OnTimeUpdate(AbstractEWPresenter* subject) {timeUpdated = true;}
        virtual void OnQuit(AbstractEWPresenter* subject) {quitUpdated = true;}
        bool checkStatUpdated() {bool temp = statUpdated; statUpdated = false; return temp;}
        bool checkTimeUpdated() {bool temp = timeUpdated; timeUpdated = false; return temp;}
        bool checkQuitUpdated() {bool temp = quitUpdated; quitUpdated = false; return temp;}
    protected:
    private:
        bool statUpdated;
        bool timeUpdated;
        bool quitUpdated;
};

#endif // OBSERVERSTUB_H
