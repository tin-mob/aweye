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


#ifndef EWAPPCONTROLLERSTUB_H
#define EWAPPCONTROLLERSTUB_H

#include "AbstractEWAppController.h"
#include "ConfigData.h"
#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractEWPresenter.h"
#include "AbstractCommand.h"

class EWAppControllerStub : public AbstractEWAppController
{
    public:
        EWAppControllerStub() : displayedDialog(false) {}
        virtual ~EWAppControllerStub() {}

        virtual bool saveConfig(const ConfigData& d) {data = d; return true;}
        virtual const ConfigData& getConfigData() const {return data;}
        virtual void displayOptionsDialog() {displayedDialog = true;}

        bool checkDisplayedDialog() {bool temp = displayedDialog; displayedDialog = false; return temp;}

        void link(AbstractMsgHandler* mh, AbstractConfig* c,
            AbstractPresenceHandler* ph, AbstractTimeKeeper* tk,
            AbstractEWPresenter* p, AbstractCommand* dc)
        {
            msgHandler = mh;
            config = c;
            presenceHandler = ph;
            timeKeeper = tk;
            presenter = p;
            displayCmd = dc;
        }

        ConfigData data;
        AbstractMsgHandler* msgHandler;
        AbstractConfig* config;
        AbstractPresenceHandler* presenceHandler;
        AbstractTimeKeeper* timeKeeper;
        AbstractEWPresenter* presenter;
        AbstractCommand* displayCmd;
    protected:
    private:
        bool displayedDialog;
};

#endif // EWAPPCONTROLLERSTUB_H
