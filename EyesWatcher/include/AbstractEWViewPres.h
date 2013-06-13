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


#ifndef ABSTRACTEWVIEWPRES_H
#define ABSTRACTEWVIEWPRES_H

/// @todo better way to go would use normal functions in a namespace...

template <class TView>
class AbstractEWViewPres
{
    public:
        virtual ~AbstractEWViewPres() {}

        void attachView(TView* view)
        {
            m_View = view;
            forceUpdate();
        }

        virtual void forceUpdate() = 0;
        virtual void OnViewQuit() = 0;
        virtual void OnViewAbout() = 0;
        virtual void OnViewOptionsButtonClick() = 0;
        virtual void OnViewStartStop() = 0;
        virtual void OnViewPauseResume() = 0;
        virtual void OnViewHideRestore() = 0;
    protected:
        TView* m_View;
        AbstractEWViewPres() : m_View(nullptr) {}
    private:
};

#endif // ABSTRACTEWVIEWPRES_H
