#ifndef ABSTRACTEWMAINFRAME_H
#define ABSTRACTEWMAINFRAME_H

#include <string>

class OptionsDialogPres;
class AbstractEWMainFrame
{
    public:
        AbstractEWMainFrame() {}
        virtual void setValues( std::string status, std::string onClock,
                               std::string offClock, std::string runningClock,
                               std::string leftClock) = 0;
        virtual void notifyMessage(std::string message, bool warning = false) = 0;
        virtual void displayOptionsDialog(OptionsDialogPres* presenter) = 0;
        virtual void show() = 0;
        virtual void setPauseButtonLabel(std::string label) = 0;
        virtual void setStartButtonLabel(std::string label) = 0;
    protected:
    private:
};

#endif // ABSTRACTEWMAINFRAME_H
