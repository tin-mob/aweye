#ifndef EWLOGIC_H
#define EWLOGIC_H

#include <string>
#include "AbstractTimeKeeper.h"

class AbstractConfig;
class HandlerFactory;
class AbstractMsgHandler;
class ConfigData;

/// @todo: really necessary ? ... If so, find a better name...
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

        AbstractTimeKeeper::Status getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getLastPause() const;
        std::string getTimeLeft() const;

    protected:
    private:
        bool m_Warn;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWLOGIC_H
