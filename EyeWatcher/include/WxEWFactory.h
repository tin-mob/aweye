#ifndef WXEWFACTORY_H
#define WXEWFACTORY_H

#include "AbstractEWFactory.h"
#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

class AbstractMsgHandler;
class AbstractConfigImpl;
class AbstractConfig;
class AbstractTimeHandler;
class AbstractPresenceHandler;
class AbstractTimeKeeper;
class AbstractTimer;
class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractOptionsDialogPres;
class AbstractEWMainFramePres;
class AbstractEWMainFrame;
class AbstractEWTaskbarPres;
class AbstractEWTaskbar;
class WxEWFactory : public AbstractEWFactory
{
    public:
        WxEWFactory();
        virtual ~WxEWFactory();

        virtual AbstractMsgHandler* createMsgHandler();
        virtual AbstractConfigImpl* createConfigImpl(std::string path);
        virtual AbstractConfig* createConfig(AbstractConfigImpl* impl);
        virtual AbstractTimeHandler* createTimeHandler();
        virtual AbstractPresenceHandler* createPresenceHandler(
            int index, std::string faceCascadeName, int faceSizeX, int faceSizeY);
        virtual AbstractTimeKeeper* createTimeKeeper(
            AbstractTimeHandler* timeHandler,
            AbstractPresenceHandler* presenceHandler,
            boost::posix_time::time_duration workLength,
            boost::posix_time::time_duration pauseLength,
            boost::posix_time::time_duration remFreq,
            boost::posix_time::time_duration checkFreq,
            unsigned int pauseTol);
        virtual AbstractTimer* createTimer();
        virtual AbstractEWPresenter* createEWPresenter(
            AbstractMsgHandler* msgHandler, AbstractTimeKeeper* keeper,
            AbstractTimer* checkTimer, AbstractTimer* clockTimer,
            bool popupAlarm, bool soundAlarm, std::string soundPath,
            boost::posix_time::time_duration runningLateThreshold);
        virtual AbstractOptionsDialogPres* createOptionsDialogPres(
            AbstractEWAppController* controller);
        virtual AbstractEWMainFramePres* createEWMainFramePres(
            AbstractEWPresenter* presenter, AbstractMsgHandler* msgHandler,
            AbstractOptionsDialogPres* optionPres);
        virtual AbstractEWMainFrame* createEWMainFrame(AbstractEWMainFramePres* pres,
            bool createdTaskBar);
        virtual AbstractEWTaskbarPres* createEWTaskBarPres(AbstractEWPresenter* presenter);
        virtual AbstractEWTaskbar* createEWTaskBar(AbstractEWTaskbarPres* presenter);
    protected:
    private:
};

#endif // WXEWFACTORY_H
