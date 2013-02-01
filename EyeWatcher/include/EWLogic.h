#ifndef EWLOGIC_H
#define EWLOGIC_H

#include <string>

class Config;
class TimeKeeper;

template <class HandlerFactory>
class EWLogic
{
    public:
        EWLogic();
        virtual ~EWLogic();

        const Config* getConfig();
        const TimeKeeper* getTimeKeeper();

        void saveConfig(
            unsigned int m_WorkLength,
            unsigned int m_PauseLength,
            unsigned int m_RemFreq,
            unsigned int m_CheckFreq,
            unsigned int m_PauseTol,
            bool m_Startup,
            bool m_SoundAlarm,
            bool m_PopupAlarm,
            bool m_EmailAlarm,
            std::string m_EmailAddr
        );

        void start();
        void stop();
        void updateStatus();


    protected:
    private:
        Config* m_Config;
        TimeKeeper* m_TimeKeeper;
};

#endif // EWLOGIC_H
