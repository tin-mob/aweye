#ifndef ABSTRACTWEBCAMHANDLER_H
#define ABSTRACTWEBCAMHANDLER_H


class AbstractWebcamHandler
{
    public:
        virtual ~AbstractWebcamHandler() {}
        virtual bool isHere() = 0;
    protected:
    private:
};

#endif // ABSTRACTWEBCAMHANDLER_H
