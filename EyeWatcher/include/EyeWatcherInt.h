#ifndef EYEWATCHERINT_H
#define EYEWATCHERINT_H

#include <string>

class Config;
class TimeKeeper;

class EyeWatcherInt
{
    public:
        static EyeWatcherInt* Instance();
        static void DisplayMsg(std::string msg);

        ~EyeWatcherInt();

        Config* getConfig();
        TimeKeeper* getTimeKeeper();

    protected:
        EyeWatcherInt();
    private:
        static EyeWatcherInt* m_Instance;

        Config* m_Config;
        TimeKeeper* m_TimeKeeper;
};

#endif // EYEWATCHERINT_H
