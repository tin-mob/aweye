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

#ifndef UTILSIMPL_H
#define UTILSIMPL_H

#include "aweye/AbstractUtils.h"
#include <wx/filefn.h>

namespace Aweye { namespace WX {

class Utils : public AbstractUtils
{
    public:
        Utils();
        virtual ~Utils();
        virtual bool fileExists(std::string name) const;
        virtual std::string getDataPath(std::string item) const;
        virtual std::string getBinPath(std::string item) const;
    protected:
    private:
        wxPathList m_DataDirs;
        wxPathList m_BinDirs;
};
}}

#endif // UTILS_H
