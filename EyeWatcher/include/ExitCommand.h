#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "Command.h"

class EyeWatcherApp;
class ExitCommand : public Command
{
    public:
        ExitCommand(EyeWatcherApp* app);
        virtual ~ExitCommand();
        virtual void execute();
    protected:
    private:
        EyeWatcherApp* m_App;
};

#endif // EXITCOMMAND_H
