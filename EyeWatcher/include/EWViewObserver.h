#ifndef EWVIEWOBSERVER_H
#define EWVIEWOBSERVER_H


class EWViewObserver
{
    public:
        virtual ~EWViewObserver() {}
        virtual void OnStatusUpdate() = 0;
        virtual void OnTimeUpdate() = 0;
        virtual void OnQuit() = 0;
    protected:
    private:
};

#endif // EWVIEWOBSERVER_H
