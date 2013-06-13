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

/// @todo use a visitor maybe?

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

    m_MsgHandler = msgHandler;
    m_Config = config;
    m_PresenceHandler = presenceHandler;
    m_TimeKeeper = timeKeeper;
    m_Presenter = presenter;
    m_DisplayCmd = displayCmd;
}

bool EWAppController::saveConfig(const ConfigData& data)
{
    try
    {
        m_Config->save(data);

        m_PresenceHandler->setCascade(data.cascadePath);
        m_PresenceHandler->setFaceSize(data.faceSizeX, data.faceSizeY);
        m_PresenceHandler->setIndex(data.webcamIndex);

        m_TimeKeeper->setCheckFreq(data.checkFreq);
        m_TimeKeeper->setPauseLength(data.pauseLength);
        m_TimeKeeper->setPauseTol(data.pauseTol);
        m_TimeKeeper->setWorkTol(data.workTol);
        m_TimeKeeper->setRemFreq(data.remFreq);
        m_TimeKeeper->setWorkLength(data.workLength);
        m_TimeKeeper->setCummulPause(data.cummulPause);

        m_Presenter->setPopupAlarm(data.popupAlarm);
        m_Presenter->setSoundAlarm(data.soundAlarm);
        m_Presenter->setSoundPath(data.soundPath);
        m_Presenter->setRunningLateThreshold(data.runningLateThreshold);
    }
    catch (BaseException e)
    {
        m_MsgHandler->displayError(e.what());
        return false;
    }
    return true;
}

const ConfigData& EWAppController::getConfigData() const
{
    return m_Config->getData();
}

void EWAppController::displayOptionsDialog()
{
    try
    {
        m_DisplayCmd->execute();
    }
    catch (BaseException e)
    {
        m_MsgHandler->displayError(e.what());
    }
}

bool EWAppController::canCreateTaskBar() const
{
    return m_CanCreateTaskbar;
}
