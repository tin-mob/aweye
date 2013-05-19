#ifndef EWBUILDER_H
#define EWBUILDER_H

#include <string>
#include "AbstractEWAppController.h"

class AbstractMsgHandler;
class AbstractConfigImpl;
class AbstractConfig;
class AbstractTimeHandler;
class AbstractPresenceHandler;
class AbstractTimeKeeper;
class AbstractTimer;
class AbstractEWPresenter;
class AbstractOptionsDialogPres;
class AbstractEWMainFramePres;
class AbstractEWMainFrame;
class AbstractEWTaskbarPres;
class AbstractEWTaskbar;
class AbstractEWFactory;
class SetTopWindowInt;
class AbstractCommand;
class ConfigData;

class EWBuilder : public AbstractEWAppController
{
    public:
        EWBuilder(AbstractEWFactory* factory, SetTopWindowInt* topInt = NULL,
                  std::string configPath = "", bool createTaskbar = true);
        virtual ~EWBuilder();

        virtual bool saveConfig(const ConfigData& data);
        virtual const ConfigData& getConfigData() const;

        virtual void displayOptionsDialog();

    protected:
    private:
        void deleteFields();

        AbstractMsgHandler* m_MsgHandler;
        AbstractConfigImpl* m_ConfigImpl;
        AbstractConfig* m_Config;
        AbstractTimeHandler* m_TimeHandler;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractTimer* m_CheckTimer;
        AbstractTimer* m_ClockTimer;
        AbstractEWPresenter* m_Presenter;
        AbstractEWMainFramePres* m_MainFramePres;
        AbstractEWMainFrame* m_MainFrame;
        AbstractEWTaskbarPres* m_TaskBarPres;
        AbstractEWTaskbar* m_TaskBar;
        AbstractOptionsDialogPres* m_OptionsPres;
        AbstractCommand* m_DisplayOptionsDialogCmd;
};

#endif // EWBUILDER_H
