#ifndef ABSTRACTCOMMAND_H
#define ABSTRACTCOMMAND_H


class AbstractCommand
{
    public:
        virtual ~AbstractCommand() {}
        virtual void execute() = 0;
    protected:
    private:
};

#endif // ABSTRACTCOMMAND_H
