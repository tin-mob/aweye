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


#ifndef ISHERECMD_H_INCLUDED
#define ISHERECMD_H_INCLUDED

namespace EW
{
enum class IsHereCmdRetCode
{
    AWAY,
    HERE,
    INVALID_NB_ARGS,
    INVALID_INDEX,
    INVALID_FACEX,
    INVALID_FACEY,
    INVALID_CASCADE,
    INVALID_CAMERA,
    OTHER_ERROR
};
}

#endif // ISHERECMD_H_INCLUDED
