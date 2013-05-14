#include "WebcamHandler.h"
#include <sstream>

// args : int index, std::string faceCascadeName, int faceSizeX, int faceSizeY
int main(int argc, char* argv[])
{
    assert(argc == 5);

    char* indexChar = argv[1];
    char* faceCascadeName = argv[2];
    char* faceSizeXChar = argv[3];
    char* faceSizeYChar = argv[4];

    std::istringstream iss(indexChar);
    int index;
    int faceSizeX;
    int faceSizeY;

    assert(iss >> index);
    iss.str(faceSizeXChar);
    iss.clear();
    assert(iss >> faceSizeX);
    iss.str(faceSizeYChar);
    iss.clear();
    assert(iss >> faceSizeY);

    WebcamHandler handler(index, faceCascadeName, faceSizeX, faceSizeY);

    return (int)handler.isHere();
}
