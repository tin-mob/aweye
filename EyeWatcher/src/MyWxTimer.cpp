#include "MyWxTimer.h"

MyWxTimer::MyWxTimer()
{
    //ctor
}

MyWxTimer::~MyWxTimer()
{
    //dtor
}

bool MyWxTimer::startTimer(long total_milliseconds, bool oneShot)
{
    return this->Start(total_milliseconds, oneShot);
}

void MyWxTimer::stopTimer()
{
    this->Stop();
}

void MyWxTimer::Notify()
{
    // sigh...
    this->notify();
}
