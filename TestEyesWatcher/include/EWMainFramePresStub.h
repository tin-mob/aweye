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

/// @todo same as EWTaskBarPresStub...

#ifndef EWMAINFRAMEPRESSTUB_H
#define EWMAINFRAMEPRESSTUB_H

#include "AbstractEWViewPres.h"
#include "AbstractEWMainFrame.h"

class AbstractCommand;
class AbstractEWPresenter;
class AbstractMsgHandler;
class EWMainFramePresStub : public AbstractEWViewPres<AbstractEWMainFrame>
{
    public:
        EWMainFramePresStub(AbstractMsgHandler& msgHandler, AbstractEWPresenter& presenter,
            AbstractCommand& dispCmd) :
            m_MsgHandler(&msgHandler), m_Presenter(&presenter), m_DispCmd(&dispCmd) {}
        virtual ~EWMainFramePresStub() {}

        virtual void forceUpdate() {}
        virtual void OnViewQuit() {}
        virtual void OnViewAbout() {}
        virtual void OnViewOptionsButtonClick() {}
        virtual void OnViewStartStop() {}
        virtual void OnViewPauseResume() {}
        virtual void OnViewHideRestore() {}

        AbstractMsgHandler* m_MsgHandler;
        AbstractEWPresenter* m_Presenter;
        AbstractCommand* m_DispCmd;
    protected:
    private:
};

#endif // EWMAINFRAMEPRESSTUB_H
