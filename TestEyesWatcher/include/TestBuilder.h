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


#ifndef TESTBUILDER_H
#define TESTBUILDER_H

#include "Builder.h"

namespace EW
{
template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TTKController,
    class TEventHandler, class TMainFramePres, class TMainFrame, class TEWTaskBarPres,
    class TEWTaskBar, class TOptionsDialogPres, class TOptionsDialog,
    class TTKConfigObserver, class TPresHdlrConfigObserver, class TEWPresConfigObserver>
class TestBuilder : public Builder<TMsgHandler, TConfigImpl,
    TConfig, TPresenceHandler, TTimeHandler, TTimeKeeper, TTimer,
    TTKController, TEventHandler, TMainFramePres, TMainFrame, TEWTaskBarPres,
    TEWTaskBar, TOptionsDialogPres, TOptionsDialog,
    TTKConfigObserver, TPresHdlrConfigObserver, TEWPresConfigObserver>
{
    public:
        TestBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar, int idOk) :
            Builder<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler, TTimeHandler,
            TTimeKeeper, TTimer, TTKController, TEventHandler, TMainFramePres,
            TMainFrame, TEWTaskBarPres, TEWTaskBar, TOptionsDialogPres, TOptionsDialog,
            TTKConfigObserver, TPresHdlrConfigObserver, TEWPresConfigObserver>
            (topInt, configPath, canCreateTaskbar, idOk),
            links(this->getBuild()){}

        virtual ~TestBuilder() {}

        const Build<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler, TTimeHandler,
            TTimeKeeper, TTimer, TTKController, TEventHandler, TMainFramePres,
            TMainFrame, TEWTaskBarPres, TEWTaskBar, TOptionsDialogPres, TOptionsDialog,
            TTKConfigObserver, TPresHdlrConfigObserver, TEWPresConfigObserver> links;
    protected:
    private:
};
}

#endif // TESTBUILDER_H
