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
        EWPresenter(AbstractMsgHandler* msgHandler, AbstractTimeKeeper* keeper,
                    AbstractTimer* checkTimer, AbstractTimer* clockTimer,
                    bool popupAlarm = true, bool soundAlarm = false, std::string soundPath = "",
                    boost::posix_time::time_duration runningLateThreshold = boost::posix_time::minutes(4));
        virtual ~EWPresenter();

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
        virtual bool isShown() const;
        virtual std::string getIconName()const;

        virtual void setRunningLateThreshold(
            boost::posix_time::time_duration runningLateThreshold);
        virtual void setPopupAlarm(bool popupAlarm);
        virtual void setSoundAlarm(bool soundAlarm);
        virtual void setSoundPath(std::string soundPath);

    protected:
    private:
        static std::string durationToString(boost::posix_time::time_duration duration);

        void alert();
        void start();
        void stop();

        bool m_Warn;
        bool m_Shown;

        AbstractTimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
        AbstractTimer* m_CheckTimer;
        AbstractTimer* m_ClockTimer;

        bool m_PopupAlarm;
        bool m_SoundAlarm;
        std::string m_SoundPath;
        boost::posix_time::time_duration m_RunningLateThreshold;
};

#endif // EWPRESENTER_H
