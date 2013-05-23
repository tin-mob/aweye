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


#ifndef EWAPPCONTROLLER_H
#define EWAPPCONTROLLER_H

#include <string>
#include "AbstractEWAppController.h"

class AbstractMsgHandler;
class AbstractConfig;
class AbstractPresenceHandler;
class AbstractTimeKeeper;
class AbstractEWPresenter;
class AbstractCommand;
class ConfigData;

class EWAppController : public AbstractEWAppController
{
    public:
        EWAppController();
        virtual ~EWAppController();

        void link(AbstractMsgHandler* msgHandler, AbstractConfig* config,
            AbstractPresenceHandler* presenceHandler, AbstractTimeKeeper* timeKeeper,
            AbstractEWPresenter* presenter, AbstractCommand* displayCmd);

        virtual bool saveConfig(const ConfigData& data);
        virtual const ConfigData& getConfigData() const;

        virtual void displayOptionsDialog();

    protected:
    private:
        void deleteFields();

        AbstractMsgHandler* m_MsgHandler;
        AbstractConfig* m_Config;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractEWPresenter* m_Presenter;
        AbstractCommand* m_DisplayOptionsDialogCmd;
};

#endif // EWAPPCONTROLLER_H
