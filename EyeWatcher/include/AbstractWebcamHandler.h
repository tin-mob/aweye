#ifndef ABSTRACTWEBCAMHANDLER_H
#define ABSTRACTWEBCAMHANDLER_H

#include <stdexcept>

class MissingCascadeFileException : public std::logic_error
{
    public:
          MissingCascadeFileException() :  std::logic_error("Missing cascade file.") { }
};

class InvalidCameraException : public std::logic_error
{
    public:
          InvalidCameraException() :  std::logic_error("Camera is not working.") { }
};

class AbstractWebcamHandler
{
    public:
        virtual ~AbstractWebcamHandler() {}
        virtual void open() = 0;
        virtual void release() = 0;
        virtual bool isHere() = 0;
    protected:
    private:
};

#endif // ABSTRACTWEBCAMHANDLER_H
