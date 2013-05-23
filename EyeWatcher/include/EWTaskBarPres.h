#ifndef EWTASKBARPRES_H
#define EWTASKBARPRES_H

#include "EWViewPres.h"
#include <string>

class AbstractEWPresenter;
class AbstractEWAppController;
class AbstractEWTaskbar;
class EWTaskBarPres : public EWViewPres<AbstractEWTaskbar>
{
    public:
        EWTaskBarPres(AbstractEWPresenter* pres, AbstractEWAppController* controller);
        virtual ~EWTaskBarPres();
    protected:
    private:
        virtual void doStatusUpdate();
        virtual void doTimeUpdate();
        virtual void doQuit();

        AbstractEWTaskbar* m_TaskBar;
        std::string m_LastIcon;
};

#endif // EWTASKBARPRES_H
