/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of EyeWatcher.

    EyeWatcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    EyeWatcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with EyeWatcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#include "EWMainFramePres.h"
#include "AbstractEWMainFrame.h"
#include "AbstractEWPresenter.h"
#include "BaseException.h"
#include "AbstractEWAppController.h"

///@todo: test this
EWMainFramePres::EWMainFramePres(AbstractEWPresenter* pres, AbstractEWAppController* controller) :
    EWViewPres(pres, controller)
{
}

EWMainFramePres::~EWMainFramePres()
{
}

void EWMainFramePres::doStatusUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    bool shown = this->m_Presenter->isShown();
    this->m_View->show(shown);
    if (shown)
    {
        this->m_View->setPauseButtonLabel(this->m_Presenter->getPauseButtonLabel());
        this->m_View->setStartButtonLabel(this->m_Presenter->getStartButtonLabel());

        // times could change in a status update (stop)
        this->m_View->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doTimeUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    if (this->m_Presenter->isShown())
    {
        this->m_View->setValues(this->m_Presenter->getStatus(), this->m_Presenter->getTimeOn(),
            this->m_Presenter->getTimeOff(), this->m_Presenter->getTimeRunning(),
            this->m_Presenter->getTimeLeft());
    }
}

void EWMainFramePres::doQuit()
{
    this->m_View->close();
}
