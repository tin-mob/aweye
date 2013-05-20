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
