#ifndef SETTOPWINDOWINT_H
#define SETTOPWINDOWINT_H

class AbstractEWMainFrame;
class SetTopWindowInt
{
    public:
        virtual ~SetTopWindowInt() {}
        virtual void setTopWindow(AbstractEWMainFrame* frame) = 0;
    protected:
    private:
};

#endif // SETTOPWINDOWINT_H
