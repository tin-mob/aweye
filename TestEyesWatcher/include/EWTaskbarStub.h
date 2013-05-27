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


#ifndef EWTASKBARSTUB_H
#define EWTASKBARSTUB_H

#include "AbstractEWTaskbar.h"

class EWTaskbarStub : public AbstractEWTaskbar
{
    public:
        EWTaskbarStub(AbstractEWViewPres<AbstractEWTaskbar>* p = nullptr) : hideRestoreLabel(""),
            startStopLabel(""), pauseResumeLabel(""), onClock(""),
            offClock(""), runningClock(""), leftClock(""),
            loc(""), presenter(p){}
        virtual ~EWTaskbarStub() {}

        virtual void setPopupMenuCommands( std::string hrl,
            std::string ssl, std::string prl)
        {
            hideRestoreLabel = hrl;
            startStopLabel = ssl;
            pauseResumeLabel = prl;
        }

        virtual void setPopupMenuTimes( std::string onc, std::string offc,
            std::string rc, std::string lc)
        {
            onClock = onc;
            offClock = offc;
            runningClock = rc;
            leftClock = lc;
        }

        virtual void setIcon(std::string l)
        {
            loc = l;
        }

        std::string hideRestoreLabel;
        std::string startStopLabel;
        std::string pauseResumeLabel;
        std::string onClock;
        std::string offClock;
        std::string runningClock;
        std::string leftClock;
        std::string loc;

        AbstractEWViewPres<AbstractEWTaskbar>* presenter;
    protected:
    private:
};


#endif // EWTASKBARSTUB_H
