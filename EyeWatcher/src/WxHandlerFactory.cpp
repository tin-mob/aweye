#include "WxHandlerFactory.h"
#include "MsgHandler.h"
#include "TimeHandler.h"
#include "WebcamHandler.h"

WxHandlerFactory::WxHandlerFactory()
{
    //ctor
}

WxHandlerFactory::~WxHandlerFactory()
{
    //dtor
}

AbstractMsgHandler* WxHandlerFactory::getMsgHandler() const
{
    return new MsgHandler();
}

AbstractTimeHandler* WxHandlerFactory::getTimeHandler() const
{
    return new TimeHandler();
}

AbstractWebcamHandler* WxHandlerFactory::getWebcamHandler() const
{
    return new WebcamHandler();
}
