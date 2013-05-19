#include "EWTaskBarPres.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWTaskbar.h"

///@todo: observer sync with view + poors man data binding

EWTaskBarPres::EWTaskBarPres(AbstractEWPresenter* presenter) :
    m_Presenter(presenter), m_TaskBar(NULL), m_LastIcon("")
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
    this->forceUpdate();
}

void EWTaskBarPres::forceUpdate()
{
    /// @todo: less hackish
    this->OnStatusUpdate(NULL);
    this->OnTimeUpdate(NULL);
}

void EWTaskBarPres::OnStatusUpdate(AbstractEWPresenter* subject)
{
    assert(this->m_TaskBar != NULL);
    if (this->m_TaskBar == NULL) return;

    this->m_TaskBar->setPopupMenuCommands(
        this->m_Presenter->getHideButtonLabel(),
        this->m_Presenter->getStartButtonLabel(),
        this->m_Presenter->getPauseButtonLabel());

    std::string newIcon = this->m_Presenter->getIconName();
    if (newIcon != this->m_LastIcon)
    {
        this->m_LastIcon = newIcon;
        this->m_TaskBar->setIcon(this->m_LastIcon);
    }
}

void EWTaskBarPres::OnTimeUpdate(AbstractEWPresenter* subject)
{
    assert(this->m_TaskBar != NULL);
    if (this->m_TaskBar == NULL) return;

    this->m_TaskBar->setPopupMenuTimes(
        "Last Session : " + this->m_Presenter->getTimeOn(),
        "Last Pause : " + this->m_Presenter->getTimeOff(),
        "Running : " + this->m_Presenter->getTimeRunning(),
        "Time Left : " + this->m_Presenter->getTimeLeft());

    std::string newIcon = this->m_Presenter->getIconName();
    if (newIcon != this->m_LastIcon)
    {
        this->m_LastIcon = newIcon;
        this->m_TaskBar->setIcon(this->m_LastIcon);
    }
}

void EWTaskBarPres::OnQuit(AbstractEWPresenter* subject)
{
    assert(this->m_TaskBar != NULL);
    if (this->m_TaskBar == NULL) return;

    this->m_TaskBar->setIcon("");
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
