#ifndef EWLOGIC_H
#define EWLOGIC_H

#include <string>

class Config;
class TimeKeeper;
class HandlerFactory;
class AbstractMsgHandler;

class EWLogic
{
    public:
        EWLogic(HandlerFactory* handlerFactory);
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
        AbstractMsgHandler* m_MsgHandler;
};

#endif // EWLOGIC_H
