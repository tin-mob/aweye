#ifndef EWPRESENTER_H
#define EWPRESENTER_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "Observer.h"
#include "AbstractEWPresenter.h"

class AbstractConfig;
class AbstractMsgHandler;
class AbstractTimeKeeper;
class AbstractPresenceHandler;
class AbstractTimer;
class ConfigData;

/// @todo: split into smallers presenters...
class EWPresenter : public Observer, public AbstractEWPresenter
{
    public:
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                    AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
                    AbstractTimer* checkTimer, AbstractTimer* clockTimer);
        virtual ~EWPresenter();

        virtual bool saveConfig(const ConfigData& data);

        virtual void togglePause();
        virtual void toggleStart();
        virtual void quit();
        virtual void show(bool show);

        void update(Observable* source);
        virtual void updateStatus();
        virtual void updateTimes();

        virtual std::string getHideButtonLabel() const;
        virtual std::string getPauseButtonLabel() const;
        virtual std::string getStartButtonLabel() const;
        virtual std::string getStatus() const;
        virtual std::string getTimeOn() const;
        virtual std::string getTimeOff() const;
        virtual std::string getTimeRunning() const;
        virtual std::string getTimeLeft() const;
        virtual const ConfigData& getConfigData() const;
        virtual bool isShown() const;
        virtual std::string getIconName()const;

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
};

#endif // EWPRESENTER_H
