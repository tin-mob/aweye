#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "Observer.h"

class AbstractConfig;
class AbstractMsgHandler;
class AbstractTimeKeeper;
class AbstractPresenceHandler;
class AbstractOptionsDialog;
class AbstractTimer;
class Command;

/// @todo: split into smallers presenters...
class EWPresenter : public Observer, public Observable
{
    public:
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                    AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
                    AbstractTimer* checkTimer, AbstractTimer* clockTimer, Command* exitCmd);
        virtual ~EWPresenter();

        bool saveConfig(const AbstractOptionsDialog* dialog);
        void loadConfig(AbstractOptionsDialog* dialog);

        void togglePause();
        void toggleStart();
        void quit();

        void update(Observable* source);
        void updateStatus();
        void updateTimes();

        std::string getPauseButtonLabel() const;
        std::string getStartButtonLabel() const;
        std::string getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getTimeRunning() const;
        std::string getTimeLeft() const;

        const std::string m_LateMsg;
        const std::string m_PauseBtnLabel;
        const std::string m_ResumeBtnLabel;
        const std::string m_StartBtnLabel;
        const std::string m_StopBtnLabel;

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();
        void start();
        void stop();

        bool m_Warn;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
        AbstractPresenceHandler* m_PresenceHandler;
        AbstractTimer* m_CheckTimer;
        AbstractTimer* m_ClockTimer;
        Command* m_ExitCmd;
};

#endif // EWPRESENTER_H
