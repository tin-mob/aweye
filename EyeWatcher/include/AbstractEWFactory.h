#ifndef ABSTRACTEWFACTORY_H
#define ABSTRACTEWFACTORY_H

#include <string>
#include "boost/date_time/posix_time/posix_time_types.hpp"

class AbstractMsgHandler;
class AbstractConfigImpl;
class AbstractConfig;
class AbstractTimeHandler;
class AbstractPresenceHandler;
class AbstractTimeKeeper;
class AbstractTimer;
class AbstractEWPresenter;
class AbstractOptionsDialogPres;
class AbstractEWMainFramePres;
class AbstractEWMainFrame;
class AbstractEWTaskbarPres;
class AbstractEWTaskbar;
class AbstractEWFactory
{
    public:
        virtual ~AbstractEWFactory() {}

        virtual AbstractMsgHandler* createMsgHandler() = 0;
        virtual AbstractConfigImpl* createConfigImpl(std::string path) = 0;
        virtual AbstractConfig* createConfig(AbstractConfigImpl* impl) = 0;
        virtual AbstractTimeHandler* createTimeHandler() = 0;
        virtual AbstractPresenceHandler* createPresenceHandler(
            int index, std::string faceCascadeName, int faceSizeX, int faceSizeY) = 0;
        virtual AbstractTimeKeeper* createTimeKeeper(
            AbstractTimeHandler* timeHandler,
            AbstractPresenceHandler* presenceHandler,
            boost::posix_time::time_duration workLength,
            boost::posix_time::time_duration pauseLength,
            boost::posix_time::time_duration remFreq,
            boost::posix_time::time_duration checkFreq,
            unsigned int pauseTol) = 0;
        virtual AbstractTimer* createTimer() = 0;
        virtual AbstractEWPresenter* createEWPresenter(
            AbstractMsgHandler* msgHandler, AbstractConfig* config,
            AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler,
            AbstractTimer* checkTimer, AbstractTimer* clockTimer) = 0;
        virtual AbstractOptionsDialogPres* createOptionsDialogPres(
            AbstractEWPresenter* presenter) = 0;
        virtual AbstractEWMainFramePres* createEWMainFramePres(
            AbstractEWPresenter* presenter, AbstractMsgHandler* msgHandler,
            AbstractOptionsDialogPres* optionPres) = 0;
        virtual AbstractEWMainFrame* createEWMainFrame(AbstractEWMainFramePres* pres,
            bool createdTaskBar) = 0;
        virtual AbstractEWTaskbarPres* createEWTaskBarPres(AbstractEWPresenter* presenter) = 0;
        virtual AbstractEWTaskbar* createEWTaskBar(AbstractEWTaskbarPres* presenter) = 0;
    protected:
    private:
};

#endif // ABSTRACTEWFACTORY_H
