#include "EWViewPres.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWAppController.h"

EWViewPres::EWViewPres(AbstractEWPresenter* presenter, AbstractEWAppController* controller) :
    m_Presenter(presenter), m_Controller(controller)
{
    assert(presenter);
    assert(controller);

    this->m_Presenter->attach(this);
}

EWViewPres::~EWViewPres()
{
    this->m_Presenter->detach(this);
}

void EWViewPres::forceUpdate()
{
    this->doStatusUpdate();
    this->doTimeUpdate();
}

void EWViewPres::OnStatusUpdate(AbstractEWPresenter*)
{
    this->doStatusUpdate();
}

void EWViewPres::OnTimeUpdate(AbstractEWPresenter*)
{
    this->doTimeUpdate();
}

void EWViewPres::OnQuit(AbstractEWPresenter*)
{
    this->doQuit();
}

void EWViewPres::OnViewQuit()
{
    this->m_Presenter->quit();
}

void EWViewPres::OnViewAbout()
{

}

void EWViewPres::OnViewOptionsButtonClick()
{
    this->m_Controller->displayOptionsDialog();
}

void EWViewPres::OnViewStartStop()
{
    this->m_Presenter->toggleStart();
}

void EWViewPres::OnViewPauseResume()
{
    this->m_Presenter->togglePause();
}

void EWViewPres::OnViewHideRestore()
{
    this->m_Presenter->show(!this->m_Presenter->isShown());
}
