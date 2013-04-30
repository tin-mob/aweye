#ifndef PRESENCEHANDLERSTUB_H
#define PRESENCEHANDLERSTUB_H

#include "AbstractPresenceHandler.h"
#include "BaseException.h"

#include <queue>
#include <assert.h>

class PresenceHandlerStub : public AbstractPresenceHandler
{
    public:
        PresenceHandlerStub() : cascadePath(""), webcamIndex(1001),
            faceSizeX(1010), faceSizeY(1011){}
        virtual ~PresenceHandlerStub() {}

        virtual bool isHere()
        {
            assert (!this->m_results.empty());
            bool result  = this->m_results.front();
            this->m_results.pop();
            return result;
        }

        virtual void pushResult(bool result)
        {
            this->m_results.push(result);
        }

        virtual void setCascade(std::string name) {cascadePath = name;}
        virtual void setIndex(int index) {webcamIndex = index;}
        virtual void setFaceSize(unsigned int x, unsigned int y) {faceSizeX = x; faceSizeY = y;}

        std::string cascadePath;
        int webcamIndex;
        unsigned int faceSizeX;
        unsigned int faceSizeY;

    protected:
    private:
        std::queue<bool> m_results;
};

#endif // PRESENCEHANDLERSTUB_H
