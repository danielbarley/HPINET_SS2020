#include "Arbiter.h"
#include "arbpkt_m.h"

Define_Module(Arbiter);

void Arbiter::initialize() {
    waitingRequests = cQueue("arbiter_queue");
    delay = static_cast<double>(par("checkingDelay"));

    scheduleAt(simTime(), new cMessage);

    //stats
    sigServiceTime = registerSignal("sigServiceTime");
    sigOutstandingRequests = registerSignal("sigOutstandingRequests");
    emit(sigOutstandingRequests, 0);
}

void Arbiter::allowNext() {
    Arbpkt * req = dynamic_cast<Arbpkt *>(waitingRequests.pop());
    emit(sigOutstandingRequests, waitingRequests.getLength());
    emit(sigServiceTime, simTime() - req->getEnqueued());
    Arbpkt * grant = new Arbpkt();
    grant->setType(1);
    grant->setSourcePort(req->getTargetOutport());
    grant->setTargetOutport(req->getSourcePort());
    send(grant, "ctrl$o", req->getSourcePort());
    processing = true;
    delete req;
}

void Arbiter::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("ctrl$i") && dynamic_cast<Arbpkt *>(msg) != nullptr) {
        if (dynamic_cast<Arbpkt *>(msg)->getType() == 0) {
            EV_INFO << "received request for grant on port "
                        << dynamic_cast<Arbpkt *>(msg)->getSourcePort() <<  endl;
            dynamic_cast<Arbpkt *>(msg)->setEnqueued(simTime());
            waitingRequests.insert(msg);
            emit(sigOutstandingRequests, waitingRequests.getLength());
        } else if (dynamic_cast<Arbpkt *>(msg)->getType() == 2) {
            if (waitingRequests.getLength() > 0) {
                allowNext();
            } else {
                processing = false;
            }
            delete msg;
        } else {
            EV_INFO << "got an unexpected Arbpkt type!" << endl;
            delete msg;
        }
    } else {
        if (msg->isSelfMessage()) {
            if (!processing && waitingRequests.getLength() > 0) {
                allowNext();
            }
            scheduleAt(simTime() + delay, msg);
        } else {
            EV_INFO << "got an unexpected message!" << endl;
            delete msg;
        }
    }
}
