#ifndef __UEB03_BUFFER_H_
#define __UEB03_BUFFER_H_

#include <omnetpp.h>

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
    double delay;
};

#endif
