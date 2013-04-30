#include "EWPresenter.h"
#include "AbstractConfig.h"
#include "HandlerFactory.h"
#include "AbstractMsgHandler.h"
#include "AbstractTimeKeeper.h"
#include "AbstractPresenceHandler.h"
#include "AbstractEWMainFrame.h"
#include "AbstractOptionsDialog.h"
#include "BaseException.h"
#include "ConfigData.h"

#include <sstream>
#include <iomanip>
#include <stdlib.h>

EWPresenter::EWPresenter(AbstractMsgHandler* msgHandler, AbstractConfig* config,
                         AbstractTimeKeeper* keeper, AbstractPresenceHandler* presenceHandler)
    :  m_LateMsg("Time for a pause!"), m_Warn(true), m_Config(config),
    m_TimeKeeper(keeper), m_MsgHandler(msgHandler), m_PresenceHandler(presenceHandler)
{
}

EWPresenter::~EWPresenter()
{
}

bool EWPresenter::saveConfig(const AbstractOptionsDialog* dialog)
{
    try
    {
        ConfigData data = dialog->getData();
        this->m_Config->save(data);

        this->m_PresenceHandler->setCascade(data.cascadePath);
        this->m_PresenceHandler->setFaceSize(data.faceSizeX, data.faceSizeY);
        this->m_PresenceHandler->setIndex(data.webcamIndex);

        this->m_TimeKeeper->setCheckFreq(data.checkFreq);
        this->m_TimeKeeper->setPauseLength(data.pauseLength);
        this->m_TimeKeeper->setPauseTol(data.pauseTol);
        this->m_TimeKeeper->setRemFreq(data.remFreq);
        this->m_TimeKeeper->setWorkLength(data.workLength);
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        return false;
    }
    return true;
}

void EWPresenter::loadConfig(AbstractOptionsDialog* dialog)
{
    dialog->setData(this->m_Config->getData());
}

void EWPresenter::start(AbstractEWMainFrame* frame)
{
    try
    {
        this->m_TimeKeeper->start();
        frame->startTimer(this->getNextStatusTimer().total_milliseconds());
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
    }
}

void EWPresenter::stop(AbstractEWMainFrame* frame)
{
    this->m_TimeKeeper->stop();
    frame->stopTimer();
}

void EWPresenter::pause()
{
    m_Warn = !m_Warn;
}

void EWPresenter::updateStatus(AbstractEWMainFrame* frame)
{
    try
    {
        this->m_TimeKeeper->updateStatus();
        frame->startTimer(this->getNextStatusTimer().total_milliseconds());

        if (this->m_TimeKeeper->isLate() && this->m_TimeKeeper->getStatus() == AbstractTimeKeeper::HERE)
        {
            this->alert();
        }
    }
    catch (BaseException e)
    {
        this->m_MsgHandler->displayError(e.what());
        this->m_TimeKeeper->stop();
    }
}

void EWPresenter::updateTimes(AbstractEWMainFrame* frame)
{
    frame->setValues(this->getStatus(), this->getTimeOn(), this->getTimeOff(),
                     this->getTimeRunning(), this->getTimeLeft());
}

boost::posix_time::time_duration EWPresenter::getNextStatusTimer() const
{
    return this->m_TimeKeeper->getTimerInterval();
}

std::string EWPresenter::getStatus() const
{
    return this->m_TimeKeeper->getStatusStr();
}

std::string EWPresenter::durationToString(boost::posix_time::time_duration duration)
{
    if (duration.is_special())
    {
        return "00:00:00";
    }
    std::stringstream out;
    if (duration.seconds() < 0)
    {
        out << "-";
    }

    out << std::setw(2) << std::setfill('0') << duration.hours() << ":" << std::setw(2)
    << std::setfill('0') << duration.minutes() << ":" << std::setw(2)
    << std::setfill('0') << abs(duration.seconds());
    return out.str();
}

std::string EWPresenter::getTimeOn() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getHereStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeOff() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getAwayStamp().time_of_day();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeRunning() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getInterval();
    return EWPresenter::durationToString(stamp);
}

std::string EWPresenter::getTimeLeft() const
{
    const boost::posix_time::time_duration stamp = this->m_TimeKeeper->getTimeLeft();
    return EWPresenter::durationToString(stamp);
}

void EWPresenter::alert()
{
    const ConfigData& config = this->m_Config->getData();
    if (config.popupAlarm)
    {
        this->m_MsgHandler->displayAlert(m_LateMsg);
    }

    if (config.soundAlarm)
    {
        ///@todo
    }

    if (config.emailAlarm)
    {
        ///@todo
    }
}
