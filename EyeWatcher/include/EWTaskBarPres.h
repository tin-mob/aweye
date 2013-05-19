#ifndef EWTASKBARPRES_H
#define EWTASKBARPRES_H

#include "EWViewObserver.h"
#include "AbstractEWTaskbarPres.h"

class AbstractEWPresenter;
class AbstractEWTaskbar;
class EWTaskBarPres : public AbstractEWTaskbarPres, public EWViewObserver
{
    public:
        EWTaskBarPres(AbstractEWPresenter* presenter);
        virtual ~EWTaskBarPres();

        virtual void attachTaskBar(AbstractEWTaskbar* taskBar);
        virtual void forceUpdate();

        virtual void OnStatusUpdate(AbstractEWPresenter* subject);
        virtual void OnTimeUpdate(AbstractEWPresenter* subject);
        virtual void OnQuit(AbstractEWPresenter* subject);

        virtual void OnMenuHideRestore();
        virtual void OnMenuStartStop();
        virtual void OnMenuPauseResume();
        virtual void OnMenuExit();
    protected:
    private:
        AbstractEWPresenter* m_Presenter;
        AbstractEWTaskbar* m_TaskBar;
        std::string m_LastIcon;
};

#endif // EWTASKBARPRES_H
