#ifndef ISHEREPROCESS_H
#define ISHEREPROCESS_H

#include <functional>
#include <wx/process.h>

// delete itself after usage
class IsHereProcess : public wxProcess
{
    public:
        static void run(std::function<void (bool)> callBack, wxString cmd);
        virtual void OnTerminate(int pid, int status);

    private:
        IsHereProcess(std::function<void (bool)> callBack);
        virtual ~IsHereProcess();

        std::function<void (bool)> m_CallBack;
};

#endif // ISHEREPROCESS_H
