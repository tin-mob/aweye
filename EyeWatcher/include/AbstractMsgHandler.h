#ifndef ABSTRACTMSGHANDLER_H
#define ABSTRACTMSGHANDLER_H

#include <string>

class AbstractMsgHandler
{
    public:
        virtual ~AbstractMsgHandler() {}
        virtual void displayError(std::string msg) = 0;
        virtual void displayAlert(std::string msg) = 0;
        virtual void playSound(std::string filename) = 0;
    protected:
    private:
};

#endif // ABSTRACTMSGHANDLER_H
