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
    int nodeID;  // own node ID
    int numNodes; // total number of nodes in Network
    simsignal_t sigPacketSent;
    simsignal_t sigPacketReceived;
    simsignal_t sigPacketReceivedSize;
};

#endif
