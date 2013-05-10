#include "EWTaskBarPres.h"
#include "EWPresenter.h"
#include "AbstractEWTaskbar.h"

EWTaskBarPres::EWTaskBarPres(EWPresenter* presenter) : m_Presenter(presenter)
{
    //ctor
    this->m_Presenter->attach(this);
}

EWTaskBarPres::~EWTaskBarPres()
{
    //dtor
}

void EWTaskBarPres::attachTaskBar(AbstractEWTaskbar* taskBar)
{
    this->m_TaskBar = taskBar;
    /// @todo: nice icons...
    this->m_TaskBar->setIcon("sample.xpm");
}

void EWTaskBarPres::update(Observable*)
{
    this->m_TaskBar->setPopupMenu(
        this->m_Presenter->getHideButtonLabel(),
        this->m_Presenter->getStartButtonLabel(),
        this->m_Presenter->getPauseButtonLabel(),
        "Last Session : " + this->m_Presenter->getTimeOn(),
        "Last Pause : " + this->m_Presenter->getTimeOff(),
        "Running : " + this->m_Presenter->getTimeRunning(),
        "Time Left : " + this->m_Presenter->getTimeLeft());
    // set icon...
}

void EWTaskBarPres::OnMenuHideRestore()
{
    this->m_Presenter->show(!this->m_Presenter->isShown());
}

void EWTaskBarPres::OnMenuStartStop()
{
    this->m_Presenter->toggleStart();
}

void EWTaskBarPres::OnMenuPauseResume()
{
    this->m_Presenter->togglePause();
}

void EWTaskBarPres::OnMenuExit()
{
    this->m_Presenter->quit();
}
