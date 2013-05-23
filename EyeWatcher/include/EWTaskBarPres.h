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


#ifndef EWTASKBARPRES_H
#define EWTASKBARPRES_H

#include "EWViewPres.h"
#include <string>

class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractEWTaskbar;
class EWTaskBarPres : public EWViewPres<AbstractEWTaskbar>
{
    public:
        EWTaskBarPres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWTaskBarPres();
    protected:
    private:
        virtual void doStatusUpdate();
        virtual void doTimeUpdate();
        virtual void doQuit();

        AbstractEWTaskbar* m_TaskBar;
        std::string m_LastIcon;
};

#endif // EWTASKBARPRES_H
