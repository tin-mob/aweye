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


#include "EWTaskBarPres.h"
#include "AbstractEWPresenter.h"
#include "AbstractEWTaskbar.h"

EWTaskBarPres::EWTaskBarPres(AbstractEWPresenter* presenter, AbstractEWAppController* controller) :
    EWViewPres(presenter, controller), m_LastIcon("")
{
}

EWTaskBarPres::~EWTaskBarPres()
{
}

void EWTaskBarPres::doStatusUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    this->m_View->setPopupMenuCommands(
        this->m_Presenter->getHideButtonLabel(),
        this->m_Presenter->getStartButtonLabel(),
        this->m_Presenter->getPauseButtonLabel());

    std::string newIcon = this->m_Presenter->getIconName();
    if (newIcon != this->m_LastIcon)
    {
        this->m_LastIcon = newIcon;
        this->m_View->setIcon(this->m_LastIcon);
    }
}

void EWTaskBarPres::doTimeUpdate()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    this->m_View->setPopupMenuTimes(
        "Last Session : " + this->m_Presenter->getTimeOn(),
        "Last Pause : " + this->m_Presenter->getTimeOff(),
        "Running : " + this->m_Presenter->getTimeRunning(),
        "Time Left : " + this->m_Presenter->getTimeLeft());

    std::string newIcon = this->m_Presenter->getIconName();
    if (newIcon != this->m_LastIcon)
    {
        this->m_LastIcon = newIcon;
        this->m_View->setIcon(this->m_LastIcon);
    }
}

void EWTaskBarPres::doQuit()
{
    assert(this->m_View != nullptr);
    if (this->m_View == nullptr) return;

    this->m_View->setIcon("");
}
