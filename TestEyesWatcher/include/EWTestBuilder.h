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


#ifndef EWTESTBUILDER_H
#define EWTESTBUILDER_H

#include "EWBuilder.h"

template <class TMsgHandler, class TConfigImpl, class TConfig, class TPresenceHandler,
    class TTimeHandler, class TTimeKeeper, class TTimer, class TEWAppController, class TEWPresenter,
    class TEWMainFramePres, class TEWMainFrame, class TEWTaskbarPres,
    class TEWTaskbar, class TOptionsDialogPres, class TBuilderOptionsDialogPres, class TDisplayOptionsDialogCmd>
class EWTestBuilder : public EWBuilder<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
    TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
    TEWMainFrame, TEWTaskbarPres, TEWTaskbar, TOptionsDialogPres, TBuilderOptionsDialogPres, TDisplayOptionsDialogCmd>
{
    public:
        EWTestBuilder(SetTopWindowInt* topInt, std::string configPath, bool canCreateTaskbar) :
            EWBuilder<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
                TEWMainFrame, TEWTaskbarPres, TEWTaskbar, TOptionsDialogPres,
                TBuilderOptionsDialogPres, TDisplayOptionsDialogCmd>
                (topInt, configPath, canCreateTaskbar),
                links(this->getBuild()){}

        virtual ~EWTestBuilder() {}

        const EWBuild<TMsgHandler, TConfigImpl, TConfig, TPresenceHandler,
                TTimeHandler, TTimeKeeper, TTimer, TEWAppController, TEWPresenter, TEWMainFramePres,
                TEWMainFrame, TEWTaskbarPres, TEWTaskbar, TOptionsDialogPres,
                TBuilderOptionsDialogPres, TDisplayOptionsDialogCmd> links;
    protected:
    private:
};

#endif // EWTESTBUILDER_H
