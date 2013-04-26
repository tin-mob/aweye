#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "AbstractTimeKeeper.h"

class AbstractConfig;
class HandlerFactory;
class AbstractMsgHandler;
class AbstractTimerHandler;
class ConfigData;

/// @todo: find a better name...
/// break into MainPresenter/AboutPresenter?
class EWPresenter
{
    public:
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config, AbstractTimeKeeper* keeper);
        virtual ~EWPresenter();

        const ConfigData& getConfigData() const;
        void saveConfig(const ConfigData& data);

        void start(AbstractTimerHandler& timerHandler);
        void stop(AbstractTimerHandler& timerHandler);
        void pause();
        void updateStatus(AbstractTimerHandler& timerHandler);

        boost::posix_time::time_duration getNextStatusTimer() const;

        std::string getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getTimeRunning() const;
        std::string getTimeLeft() const;

        const std::string m_LateMsg;

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();

        bool m_Warn;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWPRESENTER_H
