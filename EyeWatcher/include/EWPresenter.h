#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "AbstractTimeKeeper.h"

class AbstractConfig;
class HandlerFactory;
class AbstractMsgHandler;
class AbstractTimerHandler;
class AbstractEWMainFrame;
class AbstractOptionsDialog;
class ConfigData;

/// @todo: break into MainPresenter/ConfigPresenter?
class EWPresenter
{
    public:
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config, AbstractTimeKeeper* keeper);
        virtual ~EWPresenter();

        void saveConfig(const AbstractOptionsDialog* dialog);
        void loadConfig(AbstractOptionsDialog* dialog);

        void start(AbstractEWMainFrame* frame);
        void stop(AbstractEWMainFrame* frame);
        void pause();
        void updateStatus(AbstractEWMainFrame* frame);
        void updateTimes(AbstractEWMainFrame* frame);

        const std::string m_LateMsg;

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();

        boost::posix_time::time_duration getNextStatusTimer() const;

        std::string getStatus() const;
        std::string getTimeOn() const;
        std::string getTimeOff() const;
        std::string getTimeRunning() const;
        std::string getTimeLeft() const;

        bool m_Warn;
        AbstractConfig* m_Config;
        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWPRESENTER_H
