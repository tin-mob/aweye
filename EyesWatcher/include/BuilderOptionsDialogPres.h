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

#ifndef BUILDEROPTIONSDIALOGPRES_H
#define BUILDEROPTIONSDIALOGPRES_H

#include "AbstractOptionsDialogPres.h"

class AbstractConfig;
class AbstractMsgHandler;
class ConfigData;
class AbstractOptionsDialog;
class BuilderOptionsDialogPres :  public AbstractOptionsDialogPres
{
    public:
        BuilderOptionsDialogPres(AbstractConfig* config,
            AbstractMsgHandler* msgHandler, bool canCreateTaskBar);
        virtual ~BuilderOptionsDialogPres();
        virtual bool saveData(const ConfigData& data);
        virtual void init(AbstractOptionsDialog* dialog);
    protected:
    private:
        AbstractConfig* m_Config;
        AbstractMsgHandler* m_MsgHandler;
        bool m_CanCreateTaskBar;
};


#endif // BUILDEROPTIONSDIALOGPRES_H
