#ifndef SUBJECT_H
#define SUBJECT_H

// source : http://www.codeproject.com/Articles/3267/Implementing-a-Subject-Observer-pattern-with-templ
#include <list>

template <class T>
class Subject
{
    public:
        Subject() {}
        virtual ~Subject() {}

        void attach (T* observer)
        {
            m_Observers.push_back(observer);
        }

        void detach(T* observer)
        {
            m_Observers.remove(observer);
        }

        void notify(void (T::*ptMethod)())
        {
            typename std::list<T*>::iterator i = m_Observers.begin();
            typename std::list<T*>::iterator end = m_Observers.end();
            for (; i != end; ++i)
            {
                T* ptr = *i;
                (ptr->*ptMethod)();
            }
        }
    protected:
    private:
        std::list<T*> m_Observers;
};

#endif // SUBJECT_H
