#ifndef EWBUILDER_H
#define EWBUILDER_H

class MsgHandler;
class Config;
class TimeHandler;
class WebcamHandler;
class TimeKeeper;
class EWPresenter;
class EWMainFramePres;
class EWMainFrame;
class EWTaskBarPres;
class EWTaskBar;
class MyWxTimer;
class ExitCommand;
class EyeWatcherApp;
class OptionsDialogPres;
class EWBuilder
{
    public:
        EWBuilder(EyeWatcherApp* app);
        virtual ~EWBuilder();

        MsgHandler* m_MsgHandler;
        Config* m_Config;
        TimeHandler* m_TimeHandler;
        WebcamHandler* m_PresenceHandler;
        TimeKeeper* m_TimeKeeper;
        MyWxTimer* m_CheckTimer;
        MyWxTimer* m_ClockTimer;
        EWPresenter* m_Presenter;
        EWMainFramePres* m_MainFramePres;
        EWMainFrame* m_MainFrame;
        EWTaskBarPres* m_TaskBarPres;
        EWTaskBar* m_TaskBar;
        ExitCommand* m_ExitCmd;
        OptionsDialogPres* m_OptionsPres;

    protected:
    private:
        void deleteFields();
};

#endif // EWBUILDER_H
