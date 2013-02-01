#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

class AbstractMsgHandler;
class AbstractTimeHandler;
class AbstractWebcamHandler;
class HandlerFactory
{
    public:
        virtual ~HandlerFactory() {};

        virtual AbstractMsgHandler* getMsgHandler() const = 0;
        virtual AbstractTimeHandler* getTimeHandler() const = 0;
        virtual AbstractWebcamHandler* getWebcamHandler() const = 0;

    protected:
    private:
};

#endif // HANDLERFACTORY_H
