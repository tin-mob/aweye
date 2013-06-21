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

#ifndef CONFIGOBSERVERSTUBS_INCLUDED
#define CONFIGOBSERVERSTUBS_INCLUDED

#include "AbstractConfig.h"
#include "AbstractTimeKeeper.h"
#include "AbstractPresenceHandler.h"

namespace EW
{
class TKConfigObserverStub : public ConfigObserver
{
    public:
        TKConfigObserverStub(AbstractConfig& config, AbstractTimeKeeper& keeper) :
            ConfigObserver(config), m_TimeKeeper(keeper) {}
        virtual ~TKConfigObserverStub() {}

        virtual void update(const ConfigData& data) {}

        AbstractTimeKeeper& m_TimeKeeper;
};

class PresHdlrConfigObserverStub : public ConfigObserver
{
    public:
        PresHdlrConfigObserverStub(AbstractConfig& config, AbstractPresenceHandler& hdlr) :
            ConfigObserver(config), m_PresenceHandler(hdlr) {}
        virtual ~PresHdlrConfigObserverStub() {}

        virtual void update(const ConfigData& data) {}

        AbstractPresenceHandler& m_PresenceHandler;
};

class TKCtrlConfigObserverStub : public ConfigObserver
{
    public:
        TKCtrlConfigObserverStub(AbstractConfig& config, AbstractTKController& pres) :
            ConfigObserver(config), m_Presenter(pres) {}
        virtual ~TKCtrlConfigObserverStub() {}

        virtual void update(const ConfigData& data) {}

        AbstractTKController& m_Presenter;
};
}

#endif // CONFIGOBSERVERSTUBS_INCLUDED
