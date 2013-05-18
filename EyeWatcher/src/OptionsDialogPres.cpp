#include "OptionsDialogPres.h"
#include "EWPresenter.h"
#include "ConfigData.h"

OptionsDialogPres::OptionsDialogPres(AbstractEWPresenter* presenter) :m_Presenter(presenter)
{
    //ctor
}

OptionsDialogPres::~OptionsDialogPres()
{
    //dtor
}

const ConfigData& OptionsDialogPres::getData() const
{
    return this->m_Presenter->getConfigData();
}

bool OptionsDialogPres::saveData(const ConfigData& data)
{
    return this->m_Presenter->saveConfig(data);
}
