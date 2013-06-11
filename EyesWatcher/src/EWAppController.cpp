/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "EWAppController.h"
#include "ConfigData.h"
#include "BaseException.h"

#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractEWPresenter.h"
#include "AbstractCommand.h"

EWAppController::EWAppController(bool canCreateTaskbar) :
    m_MsgHandler(nullptr), m_Config(nullptr), m_PresenceHandler(nullptr),
    m_TimeKeeper(nullptr), m_Presenter(nullptr), m_DisplayCmd(nullptr),
    m_CanCreateTaskbar(canCreateTaskbar)
{
}

EWAppController::~EWAppController()
{
}

void EWAppController::link(AbstractMsgHandler* msgHandler, AbstractConfig* config,
    AbstractPresenceHandler* presenceHandler, AbstractTimeKeeper* timeKeeper,
    AbstractEWPresenter* presenter, AbstractCommand* displayCmd)
{
    assert(msgHandler);
    assert(config);
    assert(presenceHandler);
    assert(timeKeeper);
    assert(presenter);
    assert(displayCmd);

    this->m_MsgHandler = msgHandler;
    this->m_Config = config;
    this->m_PresenceHandler = presenceHandler;
    this->m_TimeKeeper = timeKeeper;
    this->m_Presenter = presenter;
    this->m_DisplayCmd = displayCmd;
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
        this->m_TimeKeeper->setWorkTol(data.workTol);
        this->m_TimeKeeper->setRemFreq(data.remFreq);
        this->m_TimeKeeper->setWorkLength(data.workLength);
        this->m_TimeKeeper->setCummulPause(data.cummulPause);

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
        this->m_DisplayCmd->execute();
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}

bool EWAppController::canCreateTaskBar() const
{
    return this->m_CanCreateTaskbar;
}
