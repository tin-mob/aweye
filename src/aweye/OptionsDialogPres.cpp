/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "aweye/AbstractConfig.h"
#include "aweye/AbstractMsgHandler.h"
#include "aweye/AbstractOptionsDialog.h"
#include "aweye/BaseException.h"
#include "aweye/ConfigData.h"
#include "aweye/OptionsDialogPres.h"

namespace Aweye {

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
    catch (const BaseException& e)
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
}
