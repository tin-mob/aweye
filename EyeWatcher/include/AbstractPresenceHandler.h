#ifndef ABSTRACTPRESENCEHANDLER_H
#define ABSTRACTPRESENCEHANDLER_H

class AbstractPresenceHandler
{
    public:
        virtual ~AbstractPresenceHandler() {}
        virtual void open() = 0;
        virtual void release() = 0;
        virtual bool isHere() = 0;
    protected:
    private:
};

#endif // ABSTRACTPRESENCEHANDLER_H
