#ifndef SETTOPWINDOWSTUB_H
#define SETTOPWINDOWSTUB_H

#include "SetTopWindowInt.h"

class AbstractEWMainFrame;
class SetTopWindowStub : public SetTopWindowInt
{
    public:
        SetTopWindowStub() : frame(nullptr){}
        virtual ~SetTopWindowStub() {}
        virtual void setTopWindow(AbstractEWMainFrame* f) {frame = f;}

        AbstractEWMainFrame* frame;
    protected:
    private:
};

#endif // SETTOPWINDOWSTUB_H
