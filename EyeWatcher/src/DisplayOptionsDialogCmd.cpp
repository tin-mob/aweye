#include "DisplayOptionsDialogCmd.h"
#include "AbstractEWAppController.h"
#include "AbstractOptionsDialogPres.h"
#include "OptionsDialog.h"

DisplayOptionsDialogCmd::DisplayOptionsDialogCmd(
    AbstractEWAppController* controller, AbstractOptionsDialogPres* presenter) :
    m_Controller(controller), m_Presenter(presenter)
{
    //ctor
}

DisplayOptionsDialogCmd::~DisplayOptionsDialogCmd()
{
    //dtor
}

void DisplayOptionsDialogCmd::execute()
{
    OptionsDialog dialog(NULL, this->m_Presenter);
    dialog.ShowModal();
}
