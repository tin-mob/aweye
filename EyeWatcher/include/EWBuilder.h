#ifndef EWBUILDER_H
#define EWBUILDER_H

class MsgHandler;
class wxConfigImpl;
class Config;
class TimeHandler;
class WebcamHandlerProc;
class TimeKeeper;
class EWPresenter;
class EWMainFramePres;
class EWMainFrame;
class EWTaskBarPres;
class EWTaskBar;
class MyWxTimer;
class EyeWatcherApp;
class OptionsDialogPres;
class EWBuilder
{
    public:
        EWBuilder(EyeWatcherApp* app, std::string configPath = "");
        virtual ~EWBuilder();

        MsgHandler* m_MsgHandler;
        wxConfigImpl* m_ConfigImpl;
        Config* m_Config;
        TimeHandler* m_TimeHandler;
        WebcamHandlerProc* m_PresenceHandler;
        TimeKeeper* m_TimeKeeper;
        MyWxTimer* m_CheckTimer;
        MyWxTimer* m_ClockTimer;
        EWPresenter* m_Presenter;
        EWMainFramePres* m_MainFramePres;
        EWMainFrame* m_MainFrame;
        EWTaskBarPres* m_TaskBarPres;
        EWTaskBar* m_TaskBar;
        OptionsDialogPres* m_OptionsPres;

    protected:
    private:
        void deleteFields();
};

#endif // EWBUILDER_H
