#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <stdexcept>
#include <string>

class BaseException : public std::logic_error
{
    public:
        BaseException(std::string str) : std::logic_error(str) {}
    protected:
    private:
};

#endif // BASEEXCEPTION_H
