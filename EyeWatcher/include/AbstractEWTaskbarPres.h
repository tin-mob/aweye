#ifndef ABSTRACTEWTASKBARPRES_H
#define ABSTRACTEWTASKBARPRES_H

class AbstractEWTaskbar;
class AbstractEWTaskbarPres
{
    public:
        virtual ~AbstractEWTaskbarPres() {}

        virtual void attachTaskBar(AbstractEWTaskbar* taskBar) = 0;
        virtual void OnStatusUpdate() = 0;
        virtual void OnTimeUpdate() = 0;
        virtual void OnQuit() = 0;

        virtual void OnMenuHideRestore() = 0;
        virtual void OnMenuStartStop() = 0;
        virtual void OnMenuPauseResume() = 0;
        virtual void OnMenuExit() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWTASKBARPRES_H
