#ifndef DISPLAYOPTIONSDIALOGCMD_H
#define DISPLAYOPTIONSDIALOGCMD_H

#include "AbstractCommand.h"

class AbstractEWAppController;
class AbstractOptionsDialogPres;
class DisplayOptionsDialogCmd : public AbstractCommand
{
    public:
        DisplayOptionsDialogCmd(AbstractEWAppController* controller,
                                AbstractOptionsDialogPres* presenter);
        virtual ~DisplayOptionsDialogCmd();
        virtual void execute();
    protected:
    private:
        AbstractEWAppController* m_Controller;
        AbstractOptionsDialogPres* m_Presenter;
};

#endif // DISPLAYOPTIONSDIALOGCMD_H
