#include "WxEWFactory.h"

#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "wxConfigImpl.h"
#include "Config.h"
#include "MsgHandler.h"
#include "WebcamHandlerProc.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "EWPresenter.h"
#include "EWMainFramePres.h"
#include "EWMainFrame.h"
#include "MyWxTimer.h"
#include "OptionsDialogPres.h"
#include "EWTaskBar.h"
#include "EWTaskBarPres.h"
#include "DisplayOptionsDialogCmd.h"

WxEWFactory::WxEWFactory()
{
    //ctor
}

WxEWFactory::~WxEWFactory()
{
    //dtor
}

AbstractMsgHandler* WxEWFactory::createMsgHandler()
{
    return new MsgHandler();
}

AbstractConfigImpl* WxEWFactory::createConfigImpl(std::string path)
{
    return new wxConfigImpl(path);
}

AbstractConfig* WxEWFactory::createConfig(AbstractConfigImpl* impl)
{
    return new Config(impl);
}

AbstractTimeHandler* WxEWFactory::createTimeHandler()
{
    return new TimeHandler();
}

AbstractPresenceHandler* WxEWFactory::createPresenceHandler(
    int index, std::string faceCascadeName, int faceSizeX, int faceSizeY)
{
    return new WebcamHandlerProc(index, faceCascadeName, faceSizeX, faceSizeY);
}

AbstractTimeKeeper* WxEWFactory::createTimeKeeper(
    AbstractTimeHandler* timeHandler,
    AbstractPresenceHandler* presenceHandler,
    boost::posix_time::time_duration workLength,
    boost::posix_time::time_duration pauseLength,
    boost::posix_time::time_duration remFreq,
    boost::posix_time::time_duration checkFreq,
    unsigned int pauseTol)
{
    return new TimeKeeper(timeHandler, presenceHandler, workLength, pauseLength,
        remFreq, checkFreq, pauseTol);
}

AbstractTimer* WxEWFactory::createTimer()
{
    return new MyWxTimer();
}

AbstractEWPresenter* WxEWFactory::createEWPresenter(
    AbstractMsgHandler* msgHandler, AbstractTimeKeeper* keeper,
    AbstractTimer* checkTimer, AbstractTimer* clockTimer,
    bool popupAlarm, bool soundAlarm, std::string soundPath,
    boost::posix_time::time_duration runningLateThreshold)
{
    return new EWPresenter(msgHandler, keeper,
        checkTimer, clockTimer, popupAlarm, soundAlarm, soundPath, runningLateThreshold);
}

AbstractOptionsDialogPres* WxEWFactory::createOptionsDialogPres(
    AbstractEWAppController* controller)
{
    return new OptionsDialogPres(controller);
}

AbstractEWMainFramePres* WxEWFactory::createEWMainFramePres(
    AbstractEWPresenter* presenter, AbstractEWAppController* controller)
{
    return new EWMainFramePres(presenter, controller);
}

AbstractEWMainFrame* WxEWFactory::createEWMainFrame(AbstractEWMainFramePres* pres,
    bool createdTaskBar)
{
    return new EWMainFrame(NULL, pres, createdTaskBar);
}

AbstractEWTaskbarPres* WxEWFactory::createEWTaskBarPres(AbstractEWPresenter* presenter)
{
    return new EWTaskBarPres(presenter);
}

AbstractEWTaskbar* WxEWFactory::createEWTaskBar(AbstractEWTaskbarPres* presenter)
{
    return new EWTaskBar(presenter);
}

AbstractCommand* WxEWFactory::createDisplayOptionsDialogCmd(
            AbstractEWAppController* controller, AbstractOptionsDialogPres* presenter)
{
    return new DisplayOptionsDialogCmd(controller, presenter);
}
