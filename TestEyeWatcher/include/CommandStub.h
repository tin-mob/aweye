#ifndef COMMANDSTUB_H
#define COMMANDSTUB_H

#include "Command.h"

class CommandStub : public Command
{
    public:
        CommandStub() : m_Executed(false) {}
        virtual ~CommandStub() {}
        virtual void execute() {m_Executed = true;}
        bool isExecuted() {bool temp = m_Executed; m_Executed = false; return temp;}
    protected:
    private:
        bool m_Executed;
};

#endif // COMMANDSTUB_H
