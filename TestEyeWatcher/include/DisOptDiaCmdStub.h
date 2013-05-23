#ifndef DISOPTDIACMDSTUB_H
#define DISOPTDIACMDSTUB_H

#include "CommandStub.h"

class DisOptDiaCmdStub : public CommandStub
{
    public:
        DisOptDiaCmdStub(AbstractEWAppController* c = nullptr,
                         AbstractOptionsDialogPres* p = nullptr) :
                         controller(c), presenter(p) {}
        virtual ~DisOptDiaCmdStub() {}

        AbstractEWAppController* controller;
        AbstractOptionsDialogPres* presenter;
    protected:
    private:
};

#endif // DISOPTDIACMDSTUB_H
