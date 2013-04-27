#ifndef WEBCAMHANDLERPROC_H
#define WEBCAMHANDLERPROC_H

#include "AbstractPresenceHandler.h"

class WebcamHandlerProc : public AbstractPresenceHandler
{
    public:
        WebcamHandlerProc(int index = 0, std::string faceCascadeName = "haarcascade_frontalface_alt.xml");
        ~WebcamHandlerProc();
        bool isHere();
    protected:
    private:
        int m_index;
        std::string m_FaceCascadeName;
};

#endif // WEBCAMHANDLERPROC_H
