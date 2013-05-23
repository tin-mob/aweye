#ifndef MSGHANDLERSTUB_H
#define MSGHANDLERSTUB_H


#include "AbstractMsgHandler.h"

#include <string>

class MsgHandlerStub : public AbstractMsgHandler
{
    public:
        MsgHandlerStub() : lastError(""), lastAlert(""), lastSound("") {}
        virtual ~MsgHandlerStub() {}
        virtual void displayError(std::string msg) {lastError = msg;}
        virtual void displayAlert(std::string msg) {lastAlert = msg;}
        virtual void playSound(std::string msg) {lastSound = msg;}
        std::string lastError;
        std::string lastAlert;
        std::string lastSound;
    protected:
    private:
};



#endif // MSGHANDLERSTUB_H
