#ifndef MSGHANDLERSTUB_H
#define MSGHANDLERSTUB_H


#include "AbstractMsgHandler.h"

#include <string>

class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : lastError("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {lastError = msg;}
        std::string lastError;
    protected:
    private:
};



#endif // MSGHANDLERSTUB_H
