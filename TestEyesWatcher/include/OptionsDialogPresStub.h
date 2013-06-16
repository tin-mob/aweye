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


#ifndef OPTIONSDIALOGPRESSTUB_H
#define OPTIONSDIALOGPRESSTUB_H

#include "AbstractConfig.h"
#include "AbstractMsgHandler.h"
#include "AbstractOptionsDialogPres.h"

class OptionsDialogPresStub : public AbstractOptionsDialogPres
{
    public:
        OptionsDialogPresStub(AbstractMsgHandler& msgHandler, AbstractConfig& config,
            bool canCreateTaskBar, bool fail = false) :
            m_MsgHandler(&msgHandler), m_Config(&config),
            m_CanCreateTaskBar(canCreateTaskBar), m_Fail(fail), m_Displayed(false) {}
        virtual ~OptionsDialogPresStub() {}

        virtual bool saveData(const ConfigData& data) {return m_Fail;}
        virtual void init(AbstractOptionsDialog& dialog) {}
        void display() {m_Displayed = true;}

        AbstractMsgHandler* m_MsgHandler;
        AbstractConfig* m_Config;
        bool m_CanCreateTaskBar;
        bool m_Fail;
        bool m_Displayed;

    protected:
    private:
};

class OptionsDialogPresStubFail : public OptionsDialogPresStub
{
    public:
        OptionsDialogPresStubFail(AbstractMsgHandler& msgHandler, AbstractConfig& config,
            bool canCreateTaskBar) :
            OptionsDialogPresStub(msgHandler, config, canCreateTaskBar, true) {}
};


#endif // OPTIONSDIALOGPRESSTUB_H
