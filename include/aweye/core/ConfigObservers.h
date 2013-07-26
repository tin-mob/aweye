/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/
 ///@note separate when situation warrants it

#ifndef CONFIGOBSERVERS_H_INCLUDED
#define CONFIGOBSERVERS_H_INCLUDED

#include "aweye/core/AbstractConfig.h"
#include "aweye/core/AbstractPresenceHandler.h"
#include "aweye/core/AbstractTimeKeeper.h"
#include "aweye/core/AbstractTKController.h"

namespace Aweye {

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

class TKCtrlConfigObserver : public ConfigObserver
{
    public:
        TKCtrlConfigObserver(AbstractConfig& config, AbstractTKController& pres) :
            ConfigObserver(config), m_TKController(pres) {}
        virtual ~TKCtrlConfigObserver() {}

        virtual void update(const ConfigData& data)
        {
            m_TKController.setPopupAlarm(data.popupAlarm);
            m_TKController.setSoundAlarm(data.soundAlarm);
            m_TKController.setSoundPath(data.soundPath);
            m_TKController.setRunningLateThreshold(data.runningLateThreshold);
        }
    private:
        AbstractTKController& m_TKController;
};
}

#endif // CONFIGOBSERVERS_H_INCLUDED
