#ifndef COMMANDSTUB_H
#define COMMANDSTUB_H

#include "AbstractCommand.h"

class CommandStub : public AbstractCommand
{
    public:
        CommandStub() : executed(false), fail(false) {}
        virtual ~CommandStub() {}
        virtual void execute()
        {
            if (fail) { throw BaseException("Testing!"); }
            executed = true;
        }
        bool executed;
        bool fail;
    protected:
    private:
};

#endif // COMMANDSTUB_H
