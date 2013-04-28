#include "EWBuilder.h"

EWBuilder::EWBuilder() :
    m_MsgHandler(NULL), m_Config(NULL), m_TimeHandler(NULL),
    m_PresenceHandler(NULL), m_TimeKeeper(NULL), m_Presenter(NULL)
{
    //ctor
    try
    {
        this->m_MsgHandler = new MsgHandler();
        try
        {
            this->m_Config = new Config();
            this->m_TimeHandler = new TimeHandler();
            this->m_PresenceHandler = new WebcamHandler();
            this->m_TimeKeeper = new TimeKeeper(m_Config, m_TimeHandler, m_PresenceHandler);
            this->m_Presenter = new EWPresenter(m_MsgHandler, m_Config, m_TimeKeeper);
        }
        catch (BaseException e)
        {
            this->m_MsgHandler->displayError(e.what());
            throw;
        }
    }
    catch (...)
    {
       this->deleteFields();
       throw; //rethrow. no memory leak
    }
}

EWBuilder::~EWBuilder()
{
    //dtor
    this->deleteFields();
}

void EWBuilder::deleteFields()
{
    if (this->m_MsgHandler != NULL) delete this->m_MsgHandler;
    if (this->m_Config != NULL) delete this->m_Config;
    if (this->m_TimeHandler != NULL) delete this->m_TimeHandler;
    if (this->m_PresenceHandler != NULL) delete this->m_PresenceHandler;
    if (this->m_TimeKeeper != NULL) delete this->m_TimeKeeper;
    if (this->m_Presenter != NULL) delete this->m_Presenter;
}
