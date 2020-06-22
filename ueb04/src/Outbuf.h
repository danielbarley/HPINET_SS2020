#ifndef __UEB04_OUTBUF_H_
#define __UEB04_OUTBUF_H_

#include <omnetpp.h>

using namespace omnetpp;

class Outbuf : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  private:
    cQueue fifo;
    double delay;
};

#endif
