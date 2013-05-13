#ifndef EWTASKBARPRES_H
#define EWTASKBARPRES_H

#include "Observer.h"

class EWPresenter;
class AbstractEWTaskbar;
class EWTaskBarPres : public Observer
{
    public:
        EWTaskBarPres(EWPresenter* presenter);
        virtual ~EWTaskBarPres();

        virtual void attachTaskBar(AbstractEWTaskbar* taskBar);
        virtual void update(Observable*);

        void OnMenuHideRestore();
        void OnMenuStartStop();
        void OnMenuPauseResume();
        void OnMenuExit();
    protected:
    private:
        EWPresenter* m_Presenter;
        AbstractEWTaskbar* m_TaskBar;
        std::string m_LastIcon;
};

#endif // EWTASKBARPRES_H
