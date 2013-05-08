#include "EWMainFramePres.h"

#include "AbstractEWMainFrame.h"
#include "EWPresenter.h"
#include "BaseException.h"
#include "AbstractMsgHandler.h"
#include "OptionsDialogPres.h"

///@todo: test this
EWMainFramePres::EWMainFramePres(EWPresenter* pres, AbstractMsgHandler* msgHandler, OptionsDialogPres* optPres) :
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
    this->m_Presenter->updateTimes();
    m_Frame->show();
}

// coarse update for now...
void EWMainFramePres::update(Observable*)
{
    assert(this->m_Frame != NULL);
    this->m_Frame->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
        this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
        this->m_Presenter->getTimeLeft());

    this->m_Frame->setPauseButtonLabel(this->m_Presenter->getPauseButtonLabel());
    this->m_Frame->setStartButtonLabel(this->m_Presenter->getStartButtonLabel());
}

void EWMainFramePres::OnQuit()
{
    assert(this->m_Frame != NULL);
    this->m_Presenter->quit();
}

void EWMainFramePres::OnAbout()
{
    assert(this->m_Frame != NULL);
}

void EWMainFramePres::OnOptionsButtonClick()
{
    assert(this->m_Frame != NULL);
    try
    {
        this->m_Frame->displayOptionsDialog(this->m_OptionsPres);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}

void EWMainFramePres::OnPlayButtonClick()
{
    assert(this->m_Frame != NULL);
    this->m_Presenter->toggleStart();
}

void EWMainFramePres::OnClose()
{
    assert(this->m_Frame != NULL);
}

void EWMainFramePres::OnPauseButtonClick()
{
    assert(this->m_Frame != NULL);
    this->m_Presenter->togglePause();
}
