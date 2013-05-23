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


#include "WebcamHandler.h"
#include <sstream>

// args : int index, std::string faceCascadeName, int faceSizeX, int faceSizeY
int main(int argc, char* argv[])
{
    assert(argc == 5);
    if (argc != 5) return -1;

    char* indexChar = argv[1];
    char* faceCascadeName = argv[2];
    char* faceSizeXChar = argv[3];
    char* faceSizeYChar = argv[4];

    std::istringstream iss(indexChar);
    int index;
    int faceSizeX;
    int faceSizeY;

    if (!iss >> index)
    {
        assert(0);
        return -1;
    }

    iss.str(faceSizeXChar);
    iss.clear();
    if (!iss >> faceSizeX)
    {
        assert(0);
        return -1;
    }

    iss.str(faceSizeYChar);
    iss.clear();
    if (!iss >> faceSizeY)
    {
        assert(0);
        return -1;
    }

    WebcamHandler handler(index, faceCascadeName, faceSizeX, faceSizeY);

    return (int)handler.isHere();
}
