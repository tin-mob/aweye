#ifndef ABSTRACTEWVIEWPRES_H
#define ABSTRACTEWVIEWPRES_H


class AbstractEWViewPres
{
    public:
        virtual ~AbstractEWViewPres() {}

        virtual void forceUpdate() = 0;
        virtual void OnViewQuit() = 0;
        virtual void OnViewAbout() = 0;
        virtual void OnViewOptionsButtonClick() = 0;
        virtual void OnViewStartStop() = 0;
        virtual void OnViewPauseResume() = 0;
        virtual void OnViewHideRestore() = 0;
    protected:
    private:
};

#endif // ABSTRACTEWVIEWPRES_H
