#ifndef MENUOBSERVER_H
#define MENUOBSERVER_H


class MenuObserver
{
    public:
        virtual ~MenuObserver() {}
        virtual void onMenuDelete(int* caller) = 0;
    protected:
    private:
};

#endif // MENUOBSERVER_H
