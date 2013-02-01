#ifndef ABSTRACTMSGHANDLER_H
#define ABSTRACTMSGHANDLER_H


class AbstractMsgHandler
{
    public:
        virtual ~AbstractMsgHandler() {}
        virtual void displayError(std::string msg) = 0;
    protected:
    private:
};

#endif // ABSTRACTMSGHANDLER_H
