#ifndef EWLOGIC_H
#define EWLOGIC_H

#include <string>
#include "AbstractTimeKeeper.h"

class AbstractConfig;
class HandlerFactory;
class AbstractMsgHandler;
class ConfigData;

/// @todo: find a better name...
/// break into MainPresenter/AboutPresenter?
class EWLogic
{
    public:
        EWLogic(AbstractMsgHandler* msgHandler, AbstractConfig* config, AbstractTimeKeeper* keeper);
        virtual ~EWLogic();

        const ConfigData& getConfigData() const;
        void saveConfig(const ConfigData& data);

        void start();
        void stop();
        void pause();
        void updateStatus();

        boost::posix_time::time_duration getNextStatusTimer() const;

        std::string getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getTimeRunning() const;
        std::string getTimeLeft() const;

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        bool m_Warn;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWLOGIC_H
