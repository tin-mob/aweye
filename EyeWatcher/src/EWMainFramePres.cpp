#include "EWMainFramePres.h"

#include "AbstractEWMainFrame.h"
#include "AbstractEWPresenter.h"
#include "BaseException.h"
#include "AbstractEWAppController.h"

///@todo: test this
EWMainFramePres::EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller) :
    EWViewPres(pres, controller)
{
}

EWMainFramePres::~EWMainFramePres()
{
}

void EWMainFramePres::doStatusUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    bool shown = this->m_Presenter->isShown();
    this->m_View->show(shown);
    if (shown)
    {
        this->m_View->setPauseButtonLabel(this->m_Presenter->getPauseButtonLabel());
        this->m_View->setStartButtonLabel(this->m_Presenter->getStartButtonLabel());

        // times could change in a status update (stop)
        this->m_View->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doTimeUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    if (this->m_Presenter->isShown())
    {
        this->m_View->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doQuit()
{
    this->m_View->close();
}
