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

#ifndef ISHEREPROCESS_H
#define ISHEREPROCESS_H

#include <functional>
#include <string>
#include <wx/process.h>

namespace EW { namespace WX {

// delete itself after usage
class IsHereProcess : public wxProcess
{
    public:
        static void run(std::function<void (bool)> callBack, std::string cmd);
        virtual void OnTerminate(int pid, int status);

    private:
        IsHereProcess(std::function<void (bool)> callBack);
        virtual ~IsHereProcess();

        std::function<void (bool)> m_CallBack;
};
}}

#endif // ISHEREPROCESS_H
