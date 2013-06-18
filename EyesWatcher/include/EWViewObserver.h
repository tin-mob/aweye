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


#ifndef EWVIEWOBSERVER_H
#define EWVIEWOBSERVER_H

///@todo change to TKObserver
class AbstractEWPresenter;
class EWViewObserver
{
    public:
        virtual ~EWViewObserver() {}
        virtual void OnStatusUpdate() = 0;
        virtual void OnTimeUpdate() = 0;
        virtual void OnQuit() = 0;
    protected:
    private:
};

#endif // EWVIEWOBSERVER_H
