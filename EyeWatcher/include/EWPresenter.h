#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "Observer.h"

class AbstractConfig;
class AbstractMsgHandler;
class AbstractTimeKeeper;
class AbstractPresenceHandler;
class AbstractTimer;
class Command;
class ConfigData;

/// @todo: split into smallers presenters...
class EWPresenter : public Observer, public Observable
{
    public:
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                    AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
                    AbstractTimer* checkTimer, AbstractTimer* clockTimer, Command* exitCmd);
        virtual ~EWPresenter();

        bool saveConfig(const ConfigData& data);

        void togglePause();
        void toggleStart();
        void quit();
        void show(bool show);

        void update(Observable* source);
        void updateStatus();
        void updateTimes();

        std::string getHideButtonLabel() const;
        std::string getPauseButtonLabel() const;
        std::string getStartButtonLabel() const;
        std::string getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getTimeRunning() const;
        std::string getTimeLeft() const;
        const ConfigData& getConfigData() const;
        bool isShown() const;
        std::string getIconName()const;

        const std::string m_LateMsg;
        const std::string m_HideBtnLabel;
        const std::string m_RestoreBtnLabel;
        const std::string m_PauseBtnLabel;
        const std::string m_ResumeBtnLabel;
        const std::string m_StartBtnLabel;
        const std::string m_StopBtnLabel;

        const std::string m_StopWebcamIcon;
        const std::string m_GreenWebcamIcon;
        const std::string m_YellowWebcamIcon;
        const std::string m_RedWebcamIcon;

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();
        void start();
        void stop();

        bool m_Warn;
        bool m_Shown;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimer* m_CheckTimer;
        AbstractTimer* m_ClockTimer;
        Command* m_ExitCmd;
};

#endif // EWPRESENTER_H
