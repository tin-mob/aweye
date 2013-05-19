#ifndef EWVIEWOBSERVER_H
#define EWVIEWOBSERVER_H

class AbstractEWPresenter;
class EWViewObserver
{
    public:
        virtual ~EWViewObserver() {}
        virtual void OnStatusUpdate(AbstractEWPresenter* subject) = 0;
        virtual void OnTimeUpdate(AbstractEWPresenter* subject) = 0;
        virtual void OnQuit(AbstractEWPresenter* subject) = 0;
    protected:
    private:
};

#endif // EWVIEWOBSERVER_H
