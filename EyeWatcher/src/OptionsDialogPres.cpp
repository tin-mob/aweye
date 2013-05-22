#include "OptionsDialogPres.h"
#include "AbstractEWAppController.h"
#include "ConfigData.h"

OptionsDialogPres::OptionsDialogPres(AbstractEWAppController* controller) :m_Controller(controller)
{
    assert(controller);
}

OptionsDialogPres::~OptionsDialogPres()
{
}

const ConfigData& OptionsDialogPres::getData() const
{
    return this->m_Controller->getConfigData();
}

bool OptionsDialogPres::saveData(const ConfigData& data)
{
    return this->m_Controller->saveConfig(data);
}
