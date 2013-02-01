#ifndef MSGHANDLER_H
#define MSGHANDLER_H

#include "AbstractMsgHandler.h"

class MsgHandler : public AbstractMsgHandler
{
    public:
        MsgHandler();
        virtual ~MsgHandler();
        virtual void displayError(std::string msg);
    protected:
    private:
};

#endif // MSGHANDLER_H
