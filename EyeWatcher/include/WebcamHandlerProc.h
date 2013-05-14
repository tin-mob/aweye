#ifndef WEBCAMHANDLERPROC_H
#define WEBCAMHANDLERPROC_H

#include "AbstractPresenceHandler.h"

class WebcamHandlerProc : public AbstractPresenceHandler
{
    public:
        WebcamHandlerProc(int index, std::string faceCascadeName,
                      int faceSizeX, int faceSizeY);
        ~WebcamHandlerProc();

        bool isHere();
        void setCascade(std::string name);
        void setIndex(int index);
        void setFaceSize(unsigned int x, unsigned int y);
    protected:
    private:
        int m_index;
        std::string m_FaceCascadeName;
        int m_FaceSizeX;
        int m_FaceSizeY;
};

#endif // WEBCAMHANDLERPROC_H
