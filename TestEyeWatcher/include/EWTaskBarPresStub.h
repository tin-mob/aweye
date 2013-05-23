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


#ifndef EWTASKBARPRESSTUB_H
#define EWTASKBARPRESSTUB_H

#include "AbstractEWViewPres.h"
#include "AbstractEWTaskbar.h"

class EWTaskBarPresStub : public AbstractEWViewPres<AbstractEWTaskbar>
{
    public:
        EWTaskBarPresStub(AbstractEWPresenter* p, AbstractEWAppController* c) :
            presenter(p), controller(c) {}
        virtual ~EWTaskBarPresStub() {}

        virtual void forceUpdate() {}
        virtual void OnViewQuit() {}
        virtual void OnViewAbout() {}
        virtual void OnViewOptionsButtonClick() {}
        virtual void OnViewStartStop() {}
        virtual void OnViewPauseResume() {}
        virtual void OnViewHideRestore() {}

        AbstractEWPresenter* presenter;
        AbstractEWAppController* controller;
    protected:
    private:
};

#endif // EWTASKBARPRESSTUB_H
