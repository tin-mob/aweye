#ifndef EWAPPCONTROLLERSTUB_H
#define EWAPPCONTROLLERSTUB_H

#include "AbstractEWAppController.h"
#include "ConfigData.h"
#include "AbstractMsgHandler.h"
#include "AbstractConfig.h"
#include "AbstractPresenceHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractEWPresenter.h"
#include "AbstractCommand.h"

class EWAppControllerStub : public AbstractEWAppController
{
    public:
        EWAppControllerStub() : displayedDialog(false) {}
        virtual ~EWAppControllerStub() {}

        virtual bool saveConfig(const ConfigData& d) {data = d; return true;}
        virtual const ConfigData& getConfigData() const {return data;}
        virtual void displayOptionsDialog() {displayedDialog = true;}

        bool checkDisplayedDialog() {bool temp = displayedDialog; displayedDialog = false; return temp;}

        void link(AbstractMsgHandler* mh, AbstractConfig* c,
            AbstractPresenceHandler* ph, AbstractTimeKeeper* tk,
            AbstractEWPresenter* p, AbstractCommand* dc)
        {
            msgHandler = mh;
            config = c;
            presenceHandler = ph;
            timeKeeper = tk;
            presenter = p;
            displayCmd = dc;
        }

        ConfigData data;
        AbstractMsgHandler* msgHandler;
        AbstractConfig* config;
        AbstractPresenceHandler* presenceHandler;
        AbstractTimeKeeper* timeKeeper;
        AbstractEWPresenter* presenter;
        AbstractCommand* displayCmd;
    protected:
    private:
        bool displayedDialog;
};

#endif // EWAPPCONTROLLERSTUB_H
