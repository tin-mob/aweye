#ifndef EWBUILDER_H
#define EWBUILDER_H

#include "Config.h"
#include "MsgHandler.h"
#include "WebcamHandler.h"
#include "TimeHandler.h"
#include "TimeKeeper.h"
#include "EWPresenter.h"

class EWBuilder
{
    public:
        EWBuilder();
        virtual ~EWBuilder();

        MsgHandler* m_MsgHandler;
        Config* m_Config;
        TimeHandler* m_TimeHandler;
        WebcamHandler* m_PresenceHandler;
        TimeKeeper* m_TimeKeeper;
        EWPresenter* m_Presenter;

    protected:
    private:
        void deleteFields();
};

#endif // EWBUILDER_H
