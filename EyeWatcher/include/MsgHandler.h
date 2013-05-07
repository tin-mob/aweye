#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include "AbstractMsgHandler.h"
#include <string>

class MsgHandler : public AbstractMsgHandler
{
    public:
        MsgHandler();
        virtual ~MsgHandler();
        virtual void displayError(std::string msg);
        virtual void displayAlert(std::string msg);
        virtual void playSound(std::string filename);
    protected:
    private:
};

#endif // MSGHANDLER_H
