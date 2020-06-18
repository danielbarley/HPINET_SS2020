#include "Arbiter.h"
#include "arbpkt_m.h"

Define_Module(Arbiter);

void Arbiter::initialize() {
}

void Arbiter::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("ctrl$i")) {
        EV_INFO << "got request from " << dynamic_cast<Arbpkt *>(msg)->getSourcePort() << endl;
        delete msg;
    } else {
        EV_INFO << "got a message from unexpected port!" << endl;
        delete msg;
    }
}
