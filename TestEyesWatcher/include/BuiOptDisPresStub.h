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

#ifndef BUIOPTDISPRESSTUB_H
#define BUIOPTDISPRESSTUB_H


#include "AbstractOptionsDialogPres.h"

class AbstractConfig;
class AbstractMsgHandler;
class BuiOptDisPresStub : public AbstractOptionsDialogPres
{
    public:
        BuiOptDisPresStub(AbstractConfig* config, AbstractMsgHandler* msgHandler,
            bool canCreateTaskBar, bool fail = false) :
            m_Config(config), m_MsgHandler(msgHandler),
            m_CanCreateTaskBar(canCreateTaskBar), m_Fail(fail) {}
        virtual ~BuiOptDisPresStub() {}

        virtual bool saveData(const ConfigData& data) {return m_Fail;}
        virtual void init(AbstractOptionsDialog* dialog) {}

        AbstractConfig* m_Config;
        AbstractMsgHandler* m_MsgHandler;
        bool m_CanCreateTaskBar;
        bool m_Fail;

    protected:
    private:
};

class BuiOptDisPresStubFail : public BuiOptDisPresStub
{
    public:
        BuiOptDisPresStubFail(AbstractConfig* config, AbstractMsgHandler* msgHandler,
            bool canCreateTaskBar) :
            BuiOptDisPresStub(config, msgHandler, canCreateTaskBar, true) {}
};

#endif // BUIOPTDISPRESSTUB_H
