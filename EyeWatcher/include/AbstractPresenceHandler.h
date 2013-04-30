#ifndef ABSTRACTPRESENCEHANDLER_H
#define ABSTRACTPRESENCEHANDLER_H

class AbstractPresenceHandler
{
    public:
        virtual ~AbstractPresenceHandler() {}
        virtual bool isHere() = 0;
        virtual void setCascade(std::string name) = 0;
        virtual void setIndex(int index) = 0;
        virtual void setFaceSize(unsigned int x, unsigned int y) = 0;
    protected:
    private:
};

#endif // ABSTRACTPRESENCEHANDLER_H
