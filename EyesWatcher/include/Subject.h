/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Eyes Watcher.

    Eyes Watcher is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Eyes Watcher is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Eyes Watcher.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/


#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>

// could have used boost::signal. Oh Well.
// Edit: more complicated to use an interface with it...
// http://stackoverflow.com/questions/2997732/how-to-convert-an-existing-callback-interface-to-use-boost-signals-slots

///@todo use refs?
template <class TObserver, class... TParams>
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

        void notify(void (TObserver::*ptMethod)(TParams...), TParams... params)
        {
            typename std::list<TObserver*>::iterator i = m_Observers.begin();
            typename std::list<TObserver*>::iterator end = m_Observers.end();
            for (; i != end; ++i)
            {
                TObserver* ptr = *i;
                (ptr->*ptMethod)(params...);
            }
        }
    protected:
    private:
        std::list<TObserver*> m_Observers;
};

#endif // SUBJECT_H

