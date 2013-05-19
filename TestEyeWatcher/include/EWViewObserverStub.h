#ifndef OBSERVERSTUB_H
#define OBSERVERSTUB_H

#include "EWViewObserver.h"

class EWViewObserverStub : public EWViewObserver
{
    public:
        EWViewObserverStub() : statUpdated(false), timeUpdated(false), quitUpdated(false){}
        virtual ~EWViewObserverStub() {}
        virtual void OnStatusUpdate(AbstractEWPresenter* subject) {statUpdated = true;}
        virtual void OnTimeUpdate(AbstractEWPresenter* subject) {timeUpdated = true;}
        virtual void OnQuit(AbstractEWPresenter* subject) {quitUpdated = true;}
        bool checkStatUpdated() {bool temp = statUpdated; statUpdated = false; return temp;}
        bool checkTimeUpdated() {bool temp = timeUpdated; timeUpdated = false; return temp;}
        bool checkQuitUpdated() {bool temp = quitUpdated; quitUpdated = false; return temp;}
    protected:
    private:
        bool statUpdated;
        bool timeUpdated;
        bool quitUpdated;
};

#endif // OBSERVERSTUB_H
