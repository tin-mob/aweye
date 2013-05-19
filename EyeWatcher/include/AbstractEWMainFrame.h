#ifndef ABSTRACTEWMAINFRAME_H
#define ABSTRACTEWMAINFRAME_H

#include <string>

class AbstractOptionsDialogPres;
class AbstractEWMainFrame
{
    public:
        AbstractEWMainFrame() {}
        virtual void setValues( std::string status, std::string onClock,
                               std::string offClock, std::string runningClock,
                               std::string leftClock) = 0;
        virtual void show(bool show = true) = 0;
        virtual void setPauseButtonLabel(std::string label) = 0;
        virtual void setStartButtonLabel(std::string label) = 0;
        virtual void close() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWMAINFRAME_H
