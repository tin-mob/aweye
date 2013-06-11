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
        EWAppControllerStub(bool cctb) :
             m_CanCreateTaskBar(cctb), m_DisplayedDialog(false) {}
        virtual ~EWAppControllerStub() {}

        virtual bool saveConfig(const ConfigData& data) {m_Data = data; return true;}
        virtual const ConfigData& getConfigData() const {return m_Data;}
        virtual void displayOptionsDialog() {m_DisplayedDialog = true;}

        bool checkDisplayedDialog() {bool temp = m_DisplayedDialog; m_DisplayedDialog = false; return temp;}

        void link(AbstractMsgHandler* mh, AbstractConfig* c,
            AbstractPresenceHandler* ph, AbstractTimeKeeper* tk,
            AbstractEWPresenter* p, AbstractCommand* dc)
        {
            m_MsgHandler = mh;
            m_Config = c;
            m_PresenceHandler = ph;
            m_TimeKeeper = tk;
            m_Presenter = p;
            m_DisplayCmd = dc;
        }

        virtual bool canCreateTaskBar() const {return m_CanCreateTaskBar;}

        ConfigData m_Data;
        AbstractMsgHandler* m_MsgHandler;
        AbstractConfig* m_Config;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractEWPresenter* m_Presenter;
        AbstractCommand* m_DisplayCmd;
        bool m_CanCreateTaskBar;
    protected:
    private:
        bool m_DisplayedDialog;
};

#endif // EWAPPCONTROLLERSTUB_H
