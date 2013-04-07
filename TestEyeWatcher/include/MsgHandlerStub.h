#ifndef MSGHANDLERSTUB_H
#define MSGHANDLERSTUB_H


#include "AbstractMsgHandler.h"

#include <string>

class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : lastError(""), lastAlert("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {lastError = msg;}
        virtual void displayAlert(std::string msg) {lastAlert = msg;}
        std::string lastError;
        std::string lastAlert;
    protected:
    private:
};



#endif // MSGHANDLERSTUB_H
