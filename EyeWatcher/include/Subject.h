#ifndef SUBJECT_H
#define SUBJECT_H

// could have used boost::signal. Oh Well.
// Edit: more complicated to use an interface with it...
// http://stackoverflow.com/questions/2997732/how-to-convert-an-existing-callback-interface-to-use-boost-signals-slots
#include <list>

template <class TObserver, class TParam>
class Subject
{
    public:
        Subject() {}
        virtual ~Subject() {}

        void attach (TObserver* observer)
        {
            m_Observers.push_back(observer);
        }

        void detach(TObserver* observer)
        {
            m_Observers.remove(observer);
        }

        void notify(void (TObserver::*ptMethod)(TParam), TParam param)
        {
            typename std::list<TObserver*>::iterator i = m_Observers.begin();
            typename std::list<TObserver*>::iterator end = m_Observers.end();
            for (; i != end; ++i)
            {
                TObserver* ptr = *i;
                (ptr->*ptMethod)(param);
            }
        }
    protected:
    private:
        std::list<TObserver*> m_Observers;
};

#endif // SUBJECT_H
