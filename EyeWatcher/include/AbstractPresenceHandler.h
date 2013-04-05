#ifndef ABSTRACTPRESENCEHANDLER_H
#define ABSTRACTPRESENCEHANDLER_H

class AbstractPresenceHandler
{
    public:
        virtual ~AbstractPresenceHandler() {}
        virtual bool isHere() = 0;
    protected:
    private:
};

#endif // ABSTRACTPRESENCEHANDLER_H
