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


#ifndef EWMAINFRAMEPRES_H
#define EWMAINFRAMEPRES_H

#include "EWViewPres.h"

class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractEWMainFrame;
class EWMainFramePres : public EWViewPres<AbstractEWMainFrame>
{
    public:
        EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWMainFramePres();
    protected:
        virtual void doStatusUpdate();
        virtual void doTimeUpdate();
        virtual void doQuit();
    private:

        AbstractEWMainFrame* m_Frame;
};

#endif // EWMAINFRAMEPRES_H
