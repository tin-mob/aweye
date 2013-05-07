#ifndef OBSERVERSTUB_H
#define OBSERVERSTUB_H

#include "Observer.h"

class ObserverStub : public Observer
{
    public:
        ObserverStub() : updated(false){}
        virtual ~ObserverStub() {}
        virtual void update(Observable*) {updated = true;}
        bool checkUpdated() {bool temp = updated; updated = false; return temp;}
    protected:
    private:
        bool updated;
};

#endif // OBSERVERSTUB_H
