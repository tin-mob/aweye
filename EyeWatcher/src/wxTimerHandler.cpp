#include "wxTimerHandler.h"
#include "wx_pch.h"

wxTimerHandler::wxTimerHandler(wxTimer* timer) : m_timer(timer)
{
    //ctor
}

wxTimerHandler::~wxTimerHandler()
{
    //dtor
}

bool wxTimerHandler::Start(int milliseconds, bool oneShot)
{
    return this->m_timer->Start(milliseconds, oneShot);
}

void wxTimerHandler::Stop()
{
    this->m_timer->Stop();
}
