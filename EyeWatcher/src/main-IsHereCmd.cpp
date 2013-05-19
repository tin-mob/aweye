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
