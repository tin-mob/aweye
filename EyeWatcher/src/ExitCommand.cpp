#include "ExitCommand.h"
#include "EyeWatcherApp.h"

ExitCommand::ExitCommand(EyeWatcherApp* app) : m_App(app)
{
    //ctor
}

ExitCommand::~ExitCommand()
{
    //dtor
}

void ExitCommand::execute()
{
    this->m_App->ExitMainLoop();
}
