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
 ///@note separate when situation warrants it

#ifndef CONFIGOBSERVERS_H_INCLUDED
#define CONFIGOBSERVERS_H_INCLUDED

#include "AbstractConfig.h"
#include "AbstractEWPresenter.h"
#include "AbstractTimeKeeper.h"
#include "AbstractPresenceHandler.h"
#include "ConfigObservers.h"

class TKConfigObserver : public ConfigObserver
{
    public:
        TKConfigObserver(AbstractConfig& config, AbstractTimeKeeper& keeper) :
            ConfigObserver(config), m_TimeKeeper(keeper) {}
        virtual ~TKConfigObserver() {}

        virtual void update(const ConfigData& data)
        {
            m_TimeKeeper.setCheckFreq(data.checkFreq);
            m_TimeKeeper.setPauseLength(data.pauseLength);
            m_TimeKeeper.setPauseTol(data.pauseTol);
            m_TimeKeeper.setWorkTol(data.workTol);
            m_TimeKeeper.setRemFreq(data.remFreq);
            m_TimeKeeper.setWorkLength(data.workLength);
            m_TimeKeeper.setCummulPause(data.cummulPause);
        }
    private:
        AbstractTimeKeeper& m_TimeKeeper;
};

class PresHdlrConfigObserver : public ConfigObserver
{
    public:
        PresHdlrConfigObserver(AbstractConfig& config, AbstractPresenceHandler& hdlr) :
            ConfigObserver(config), m_PresenceHandler(hdlr) {}
        virtual ~PresHdlrConfigObserver() {}

        virtual void update(const ConfigData& data)
        {
            m_PresenceHandler.setCascade(data.cascadePath);
            m_PresenceHandler.setFaceSize(data.faceSizeX, data.faceSizeY);
            m_PresenceHandler.setIndex(data.webcamIndex);
        }

    private:
        AbstractPresenceHandler& m_PresenceHandler;
};

class EWPresConfigObserver : public ConfigObserver
{
    public:
        EWPresConfigObserver(AbstractConfig& config, AbstractEWPresenter& pres) :
            ConfigObserver(config), m_Presenter(pres) {}
        virtual ~EWPresConfigObserver() {}

        virtual void update(const ConfigData& data)
        {
            m_Presenter.setPopupAlarm(data.popupAlarm);
            m_Presenter.setSoundAlarm(data.soundAlarm);
            m_Presenter.setSoundPath(data.soundPath);
            m_Presenter.setRunningLateThreshold(data.runningLateThreshold);
        }
    private:
        AbstractEWPresenter& m_Presenter;
};

#endif // CONFIGOBSERVERS_H_INCLUDED
