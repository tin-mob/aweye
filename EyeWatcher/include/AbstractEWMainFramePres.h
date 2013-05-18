#ifndef ABSTRACTEWMAINFRAMEPRES_H
#define ABSTRACTEWMAINFRAMEPRES_H

class AbstractEWMainFrame;
class AbstractEWMainFramePres
{
    public:
        virtual ~AbstractEWMainFramePres() {}

        virtual void attachFrame(AbstractEWMainFrame* frame) = 0;
        virtual void OnStatusUpdate() = 0;
        virtual void OnTimeUpdate() = 0;
        virtual void OnQuit() = 0;

        virtual void OnFrameQuit() = 0;
        virtual void OnFrameAbout() = 0;
        virtual void OnFrameOptionsButtonClick() = 0;
        virtual void OnFramePlayButtonClick() = 0;
        virtual void OnFramePauseButtonClick() = 0;
        virtual void OnFrameClose() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWMAINFRAMEPRES_H
