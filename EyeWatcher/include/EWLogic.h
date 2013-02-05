#ifndef EWLOGIC_H
#define EWLOGIC_H

#include <string>

class AbstractConfig;
class TimeKeeper;
class HandlerFactory;
class AbstractMsgHandler;

class EWLogic
{
    public:
        EWLogic(AbstractMsgHandler* msgHandler, AbstractConfig* config, TimeKeeper* keeper);
        virtual ~EWLogic();

        const AbstractConfig* getConfig();
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
        AbstractConfig* m_Config;
        TimeKeeper* m_TimeKeeper;
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWLOGIC_H
