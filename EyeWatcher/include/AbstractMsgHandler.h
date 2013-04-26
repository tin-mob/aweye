#ifndef ABSTRACTMSGHANDLER_H
#define ABSTRACTMSGHANDLER_H

// Maybe should be in a singleton rather than be injected where needed
class AbstractMsgHandler
{
    public:
        virtual ~AbstractMsgHandler() {}
        virtual void displayError(std::string msg) = 0;
        virtual void displayAlert(std::string msg) = 0;
    protected:
    private:
};

#endif // ABSTRACTMSGHANDLER_H
