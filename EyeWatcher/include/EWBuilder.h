#ifndef EWBUILDER_H
#define EWBUILDER_H

#include <string>

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
class EWBuilder
{
    public:
        EWBuilder(AbstractEWFactory* factory, SetTopWindowInt* topInt = NULL,
                  std::string configPath = "", bool createTaskbar = true);
        virtual ~EWBuilder();

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

    protected:
    private:
        void deleteFields();
};

#endif // EWBUILDER_H
