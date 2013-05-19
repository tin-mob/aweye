#include "EWMainFramePres.h"

#include "AbstractEWMainFrame.h"
#include "AbstractEWPresenter.h"
#include "BaseException.h"
#include "AbstractMsgHandler.h"
#include "AbstractOptionsDialogPres.h"

///@todo: test this
EWMainFramePres::EWMainFramePres(AbstractEWPresenter* pres, AbstractMsgHandler* msgHandler, AbstractOptionsDialogPres* optPres) :
    m_Presenter(pres), m_Frame(NULL), m_MsgHandler(msgHandler), m_OptionsPres(optPres)
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

    // force update
    /// @todo: less hackish
    this->OnStatusUpdate(NULL);
    this->OnTimeUpdate(NULL);
}

void EWMainFramePres::OnStatusUpdate(AbstractEWPresenter* subject)
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

void EWMainFramePres::OnTimeUpdate(AbstractEWPresenter* subject)
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

void EWMainFramePres::OnQuit(AbstractEWPresenter* subject)
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
    assert(this->m_Frame != NULL);
    if (this->m_Frame == NULL) return;

    try
    {
        this->m_Frame->displayOptionsDialog(this->m_OptionsPres);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
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
