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

#include "IsHereCmd.h"
#include "WebcamHandler.h"
#include <sstream>

// args : int index, std::string faceCascadeName, int faceSizeX, int faceSizeY
int main(int argc, char* argv[])
{
    assert(argc == 5);
    if (argc != 5) return IsHereCmd::INVALID_NB_ARGS;

    const char* indexChar = argv[1];
    const char* faceCascadeName = argv[2];
    const char* faceSizeXChar = argv[3];
    const char* faceSizeYChar = argv[4];

    std::istringstream iss(indexChar);
    int index = 0;
    int faceSizeX = 0;
    int faceSizeY = 0;

    if (!iss >> index)
    {
        assert(0);
        return IsHereCmd::INVALID_INDEX;
    }

    iss.str(faceSizeXChar);
    iss.clear();
    if (!iss >> faceSizeX)
    {
        assert(0);
        return IsHereCmd::INVALID_FACEX;
    }

    iss.str(faceSizeYChar);
    iss.clear();
    if (!iss >> faceSizeY)
    {
        assert(0);
        return IsHereCmd::INVALID_FACEY;
    }

    try
    {
        WebcamHandler handler(index, faceCascadeName, faceSizeX, faceSizeY);
        if(handler.isHere())
        {
            return IsHereCmd::HERE;
        }
        else
        {
            return IsHereCmd::AWAY;
        }
    }
    catch (MissingCascadeFileException)
    {
        return IsHereCmd::INVALID_CASCADE;
    }
    catch (InvalidCameraException)
    {
        return IsHereCmd::INVALID_CAMERA;
    }
    catch (...)
    {
        return IsHereCmd::OTHER_ERROR;
    }
}
