#ifndef __UEB03_BUFFER_H_
#define __UEB03_BUFFER_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Buffer : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  private:
    cQueue fifo;
    cQueue tFifo;
    double delay;

    simsignal_t sigNumInQueue;
    simsignal_t sigTimeInQueue;
    simsignal_t sigNumDiscarded;
    simsignal_t sigBusyLine;
};

#endif
