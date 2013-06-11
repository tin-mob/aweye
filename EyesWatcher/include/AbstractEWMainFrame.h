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


#ifndef ABSTRACTEWMAINFRAME_H
#define ABSTRACTEWMAINFRAME_H

#include <string>

class AbstractOptionsDialogPres;
class AbstractEWMainFrame
{
    public:
        AbstractEWMainFrame() {}
        virtual void setValues( std::string statusLabel, std::string onClockLabel,
                               std::string offClockLabel, std::string runningClockLabel,
                               std::string leftClockLabel) = 0;
        virtual void show(bool show = true) = 0;
        virtual void setPauseButtonLabel(std::string label) = 0;
        virtual void setStartButtonLabel(std::string label) = 0;
        virtual void close() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWMAINFRAME_H
