#ifndef __UEB04_ARBITER_H_
#define __UEB04_ARBITER_H_

#include <omnetpp.h>

using namespace omnetpp;

class Arbiter : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    cQueue waitingRequests;
    bool processing = false;
    double delay;
    virtual void allowNext();
};

#endif
