#ifndef __UEB02_APP_H_
#define __UEB02_APP_H_

#include <omnetpp.h>

using namespace omnetpp;

class App : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  private:
    long nodeID;
    double sendDelay;
};

#endif
