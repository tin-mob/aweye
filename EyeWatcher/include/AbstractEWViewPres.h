#ifndef ABSTRACTEWVIEWPRES_H
#define ABSTRACTEWVIEWPRES_H


template <class TView>
class AbstractEWViewPres
{
    public:
        virtual ~AbstractEWViewPres() {}

        void attachView(TView* view)
        {
            this->m_View = view;
            this->forceUpdate();
        }

        virtual void forceUpdate() = 0;
        virtual void OnViewQuit() = 0;
        virtual void OnViewAbout() = 0;
        virtual void OnViewOptionsButtonClick() = 0;
        virtual void OnViewStartStop() = 0;
        virtual void OnViewPauseResume() = 0;
        virtual void OnViewHideRestore() = 0;
    protected:
        TView* m_View;
        AbstractEWViewPres() : m_View(nullptr) {}
    private:
};

#endif // ABSTRACTEWVIEWPRES_H
