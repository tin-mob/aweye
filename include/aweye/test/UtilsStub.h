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

#ifndef UTILSIMPLSTUB_H
#define UTILSIMPLSTUB_H

#include "aweye/AbstractUtils.h"

#include <string>

namespace Aweye {

class UtilsStub : public AbstractUtils
{
    public:
        UtilsStub(std::string failName = "", std::string dataDir = "") :
            m_FailName(failName), m_DataDir(dataDir) {}
        virtual ~UtilsStub() {}

        virtual bool fileExists(std::string name) const
        {
            if (name == m_FailName)
            {
                return false;
            }
            return true;
        }

        virtual std::string getDataPath(std::string item) const
        {
            return m_DataDir + item;
        }

        std::string m_FailName;
        std::string m_DataDir;
    protected:
    private:
};
}

#endif // UTILSIMPLSTUB_H