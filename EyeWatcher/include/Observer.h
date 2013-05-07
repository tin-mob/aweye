#ifndef OBSERVER_H
#define OBSERVER_H

#include <list>

/// @todo: create cpp file?
class Observable;
class Observer
{
    public:
        virtual ~Observer() {}
        virtual void update(Observable*) = 0;
};

class Observable
{
    public:
        virtual ~Observable() {}
        virtual void attach(Observer* o)
        {
            m_Observers.push_back(o);
        }
        virtual void detach(Observer* o)
        {
            m_Observers.remove(o);
        }
        virtual void notify()
        {
            std::list<Observer*>::iterator i = m_Observers.begin();
            std::list<Observer*>::iterator end = m_Observers.end();
            for (; i != end; ++i)
            {
                (*i)->update(this);
            }
        }
    protected:
        Observable() {};
    private:
        std::list<Observer*> m_Observers;
};

#endif // OBSERVER_H
