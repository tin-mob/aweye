#ifndef WXHANDLERFACTORY_H
#define WXHANDLERFACTORY_H

#include "HandlerFactory.h"

class WxHandlerFactory : public HandlerFactory
{
    public:
        WxHandlerFactory();
        virtual ~WxHandlerFactory();

        AbstractMsgHandler* getMsgHandler() const;
        AbstractTimeHandler* getTimeHandler() const;
        AbstractWebcamHandler* getWebcamHandler() const;
    protected:
    private:
};

#endif // WXHANDLERFACTORY_H
