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


#ifndef TKCONTROLLEROBSERVER_H
#define TKCONTROLLEROBSERVER_H

namespace Aweye {

class TKControllerObserver
{
    public:
        virtual ~TKControllerObserver() {}
        virtual void OnStatusUpdate() = 0;
        virtual void OnTimeUpdate() = 0;
        virtual void OnQuit() = 0;
    protected:
    private:
};
}

#endif // TKCONTROLLEROBSERVER_H
