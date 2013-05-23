#ifndef PRESENCEHANDLERSTUB_H
#define PRESENCEHANDLERSTUB_H

#include "AbstractPresenceHandler.h"
#include "BaseException.h"

#include <queue>
#include <assert.h>

class PresenceHandlerStub : public AbstractPresenceHandler
{
    public:
        PresenceHandlerStub(int i = 1001, std::string fcn = "", int fx = 1010, int fy = 1011) :
            cascadePath(fcn), webcamIndex(i), faceSizeX(fx), faceSizeY(fy){}
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
