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

#include "AbstractConfig.h"
#include "AbstractMsgHandler.h"
#include "AbstractOptionsDialog.h"
#include "BaseException.h"
#include "ConfigData.h"
#include "OptionsDialogPres.h"

OptionsDialogPres::OptionsDialogPres(AbstractMsgHandler& msgHandler, AbstractConfig& config, bool canCreateTaskBar) :
    m_MsgHandler(msgHandler), m_Config(config), m_CanCreateTaskBar(canCreateTaskBar)
{
}

OptionsDialogPres::~OptionsDialogPres()
{
}

bool OptionsDialogPres::saveData(const ConfigData& data)
{
    try
    {
        m_Config.save(data);
    }
    catch (BaseException e)
    {
        m_MsgHandler.displayError(e.what());
        return false;
    }
    return true;
}

void OptionsDialogPres::init(AbstractOptionsDialog& dialog)
{
    dialog.setData(m_Config.getData());
    if (!m_CanCreateTaskBar)
    {
        dialog.disableTray();
    }
}
