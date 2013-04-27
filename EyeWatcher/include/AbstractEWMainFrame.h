#ifndef ABSTRACTEWMAINFRAME_H
#define ABSTRACTEWMAINFRAME_H


class AbstractEWMainFrame
{
    public:
        AbstractEWMainFrame() {}
        virtual void setValues( std::string status, std::string onClock,
                               std::string offClock, std::string runningClock,
                               std::string leftClock) = 0;

        virtual void startTimer(long total_milliseconds) = 0;
        virtual void stopTimer() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWMAINFRAME_H
