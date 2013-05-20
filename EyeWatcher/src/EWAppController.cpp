#include "EWAppController.h"
#include "ConfigData.h"
#include "BaseException.h"

#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractEWPresenter.h"
#include "AbstractCommand.h"

EWAppController::EWAppController() :
    m_MsgHandler(NULL), m_Config(NULL), m_PresenceHandler(NULL),
    m_TimeKeeper(NULL), m_Presenter(NULL), m_DisplayOptionsDialogCmd(NULL)
{
    //ctor
}

EWAppController::~EWAppController()
{
    //dtor
}

void EWAppController::link(AbstractMsgHandler* msgHandler, AbstractConfig* config,
    AbstractPresenceHandler* presenceHandler, AbstractTimeKeeper* timeKeeper,
    AbstractEWPresenter* presenter, AbstractCommand* displayCmd)
{
    this->m_MsgHandler = msgHandler;
    this->m_Config = config;
    this->m_PresenceHandler = presenceHandler;
    this->m_TimeKeeper = timeKeeper;
    this->m_Presenter = presenter;
    this->m_DisplayOptionsDialogCmd = displayCmd;
}

bool EWAppController::saveConfig(const ConfigData& data)
{
    try
    {
        this->m_Config->save(data);

        this->m_PresenceHandler->setCascade(data.cascadePath);
        this->m_PresenceHandler->setFaceSize(data.faceSizeX, data.faceSizeY);
        this->m_PresenceHandler->setIndex(data.webcamIndex);

        this->m_TimeKeeper->setCheckFreq(data.checkFreq);
        this->m_TimeKeeper->setPauseLength(data.pauseLength);
        this->m_TimeKeeper->setPauseTol(data.pauseTol);
        this->m_TimeKeeper->setRemFreq(data.remFreq);
        this->m_TimeKeeper->setWorkLength(data.workLength);

        this->m_Presenter->setPopupAlarm(data.popupAlarm);
        this->m_Presenter->setSoundAlarm(data.soundAlarm);
        this->m_Presenter->setSoundPath(data.soundPath);
        this->m_Presenter->setRunningLateThreshold(data.runningLateThreshold);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        return false;
    }
    return true;
}

const ConfigData& EWAppController::getConfigData() const
{
    return this->m_Config->getData();
}

void EWAppController::displayOptionsDialog()
{
    try
    {
        this->m_DisplayOptionsDialogCmd->execute();
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}
