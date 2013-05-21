#include "EWMainFramePres.h"

#include "AbstractEWMainFrame.h"
#include "AbstractEWPresenter.h"
#include "BaseException.h"
#include "AbstractEWAppController.h"

///@todo: test this
EWMainFramePres::EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller) :
    m_Presenter(pres), m_Frame(NULL), m_Controller(controller)
{
    //ctor
    this->m_Presenter->attach(this);
}

EWMainFramePres::~EWMainFramePres()
{
}

void EWMainFramePres::attachFrame(AbstractEWMainFrame* frame)
{
    this->m_Frame = frame;
    this->doStatusUpdate();
    this->doTimeUpdate();
}

void EWMainFramePres::OnStatusUpdate(AbstractEWPresenter*)
{
    this->doStatusUpdate();
}

void EWMainFramePres::OnTimeUpdate(AbstractEWPresenter*)
{
    this->doTimeUpdate();
}

void EWMainFramePres::OnQuit(AbstractEWPresenter*)
{
    this->doQuit();
}

void EWMainFramePres::doStatusUpdate()
{
    assert(this->m_Frame != NULL);
    if (this->m_Frame == NULL) return;

    bool shown = this->m_Presenter->isShown();
    this->m_Frame->show(shown);
    if (shown)
    {
        this->m_Frame->setPauseButtonLabel(this->m_Presenter->getPauseButtonLabel());
        this->m_Frame->setStartButtonLabel(this->m_Presenter->getStartButtonLabel());

        // times could change in a status update (stop)
        this->m_Frame->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doTimeUpdate()
{
    assert(this->m_Frame != NULL);
    if (this->m_Frame == NULL) return;

    bool shown = this->m_Presenter->isShown();
    if (shown)
    {
        this->m_Frame->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doQuit()
{
    this->m_Frame->close();
}

void EWMainFramePres::OnFrameQuit()
{
    this->m_Presenter->quit();
}

void EWMainFramePres::OnFrameAbout()
{
}

void EWMainFramePres::OnFrameOptionsButtonClick()
{
    this->m_Controller->displayOptionsDialog();
}

void EWMainFramePres::OnFramePlayButtonClick()
{
    this->m_Presenter->toggleStart();
}

void EWMainFramePres::OnFrameClose()
{
    this->m_Presenter->show(false);
}

void EWMainFramePres::OnFramePauseButtonClick()
{
    this->m_Presenter->togglePause();
}
