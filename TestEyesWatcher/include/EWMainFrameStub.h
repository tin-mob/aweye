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


#ifndef EWMAINFRAMESTUB_H
#define EWMAINFRAMESTUB_H

#include "AbstractEWMainFrame.h"
#include "AbstractEWViewPres.h"

class EWMainFrameStub : public AbstractEWMainFrame
{
    public:
        EWMainFrameStub(AbstractEWViewPres<AbstractEWMainFrame>* p = nullptr,
            bool tc = true) :
            closed(false), shown(false), status(""),
            onClock(""), offClock(""), runningClock(""), leftClock(""),
            pauseLabel(""), startLabel(""), presenter(p), taskbarCreated(tc) {}
        virtual ~EWMainFrameStub() {}

        virtual void setValues( std::string s, std::string onC,
                               std::string offC, std::string r,
                               std::string l)
        {
            status = s;
            onClock = onC;
            offClock = offC;
            runningClock = r;
            leftClock = l;
        }

        virtual void show(bool show = true) {shown = show;}

        bool closed;
        bool shown;
        std::string status;
        std::string onClock;
        std::string offClock;
        std::string runningClock;
        std::string leftClock;
        std::string pauseLabel;
        std::string startLabel;

        AbstractEWViewPres<AbstractEWMainFrame>* presenter;
        bool taskbarCreated;

        virtual void setPauseButtonLabel(std::string label) {pauseLabel = label;}
        virtual void setStartButtonLabel(std::string label) {startLabel = label;}
        virtual void close() {closed = true;}

    protected:
    private:
};

#endif // EWMAINFRAMESTUB_H
