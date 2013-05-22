#include "DisplayOptionsDialogCmd.h"
#include "AbstractEWAppController.h"
#include "AbstractOptionsDialogPres.h"
#include "OptionsDialog.h"

///@todo: remove unnecessary param
DisplayOptionsDialogCmd::DisplayOptionsDialogCmd(
    AbstractEWAppController* controller, AbstractOptionsDialogPres* presenter) :
    m_Controller(controller), m_Presenter(presenter)
{
    assert(controller);
    assert(presenter);
}

DisplayOptionsDialogCmd::~DisplayOptionsDialogCmd()
{
}

void DisplayOptionsDialogCmd::execute()
{
    OptionsDialog dialog(NULL, this->m_Presenter);
    dialog.ShowModal();
}
