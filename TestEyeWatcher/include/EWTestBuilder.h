#ifndef EWTESTBUILDER_H
#define EWTESTBUILDER_H

#include "EWBuilder.h"

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController, class TEWPresenter,
    class TEWMainFramePres, class TEWMainFrame, class TOptionsDialogPres, class TEWTaskbarPres,
    class TEWTaskbar, class TDisplayOptionsDialogCmd>
struct EWTestBuilderLinks
{
    const TMsgHandler* m_MsgHandler;
    const TConfigImpl* m_ConfigImpl;
    const TConfig* m_Config;
    const TPresenceHandler* m_PresenceHandler;
    const TTimeHandler* m_TimeHandler;
    const TTimeKeeper* m_TimeKeeper;
    const TTimer* m_CheckTimer;
    const TTimer* m_ClockTimer;
    const TEWAppController* m_AppController;
    const TEWPresenter* m_Presenter;
    const TEWMainFramePres* m_MainFramePres;
    const TEWMainFrame* m_MainFrame;
    const TOptionsDialogPres* m_OptionsPres;
    const TEWTaskbarPres* m_TaskBarPres;
    const TEWTaskbar* m_TaskBar;
    const TDisplayOptionsDialogCmd* m_DisplayOptionsDialogCmd;
};

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController, class TEWPresenter,
    class TEWMainFramePres, class TEWMainFrame, class TOptionsDialogPres, class TEWTaskbarPres,
    class TEWTaskbar, class TDisplayOptionsDialogCmd>
class EWTestBuilder : public EWBuilder<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
    TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
    TEWMainFrame, TOptionsDialogPres, TEWTaskbarPres, TEWTaskbar, TDisplayOptionsDialogCmd>
{
    public:
        EWTestBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar) :
            EWBuilder<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
                TEWMainFrame, TOptionsDialogPres, TEWTaskbarPres, TEWTaskbar, TDisplayOptionsDialogCmd>
                (topInt, configPath, canCreateTaskbar),
                links({this->m_MsgHandler, this->m_ConfigImpl, this->m_Config,
                      this->m_PresenceHandler, this->m_TimeHandler, this->m_TimeKeeper,
                      this->m_CheckTimer, this->m_ClockTimer, this->m_AppController,
                      this->m_Presenter, this->m_MainFramePres, this->m_MainFrame,
                      this->m_OptionsPres, this->m_TaskBarPres, this->m_TaskBar,
                      this->m_DisplayOptionsDialogCmd}){}

        virtual ~EWTestBuilder() {}

        EWTestBuilderLinks<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter,
                TEWMainFramePres, TEWMainFrame, TOptionsDialogPres, TEWTaskbarPres,
                TEWTaskbar, TDisplayOptionsDialogCmd> links;
    protected:
    private:
};

#endif // EWTESTBUILDER_H
