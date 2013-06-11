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


#include "OptionsDialogPres.h"
#include "AbstractEWAppController.h"
#include "ConfigData.h"
#include "AbstractOptionsDialog.h"

OptionsDialogPres::OptionsDialogPres(AbstractEWAppController* controller) :m_Controller(controller)
{
    assert(controller);
}

OptionsDialogPres::~OptionsDialogPres()
{
}

bool OptionsDialogPres::saveData(const ConfigData& data)
{
    return m_Controller->saveConfig(data);
}

void OptionsDialogPres::init(AbstractOptionsDialog* dialog)
{
    dialog->setData(m_Controller->getConfigData());
    if (!m_Controller->canCreateTaskBar())
    {
        dialog->disableTray();
    }
}
