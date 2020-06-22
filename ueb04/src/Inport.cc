#include "Inport.h"

#include "arbpkt_m.h"
#include "packet_m.h"

Define_Module(Inport);

void Inport::initialize() {
    fifo = cQueue("inport_buffer");
    delay = static_cast<double>(par("checkingDelay"));
    scheduleAt(simTime(), new cMessage);  // timer event for checking line$o

    sigQlength = registerSignal("sigQlength");
    sigQtime = registerSignal("sigQtime");

    WATCH(granted);
    //WATCH(front);
}

void Inport::requestArbitration(int sourcePort, int targetPort) {
    Arbpkt *req = new Arbpkt();
    req->setType(0);
    req->setSourcePort(sourcePort);
    req->setTargetOutport(targetPort);
    EV_INFO << "requesting grant from arbiter " << targetPort << endl;
    send(req, "arbiterCtrl$o", targetPort);

    waiting = true;

    arbiterWait = targetPort;
    sourceWait = sourcePort;
}

void Inport::releaseArbitration(int sourcePort, int targetPort) {
    Arbpkt *rel = new Arbpkt();
    rel->setType(2);
    rel->setTargetOutport(targetPort);
    rel->setSourcePort(sourcePort);
    EV_INFO << "releasing grant from arbiter " << targetPort << endl;
    send(rel, "arbiterCtrl$o", targetPort);
    granted = false;
}

void Inport::handleMessage(cMessage *msg) {
    emit(sigQlength, fifo.getLength());
    if (msg->isSelfMessage()) {  // timer interval and we can send
        if (granted) {
            simtime_t finishtime = gate("line$o", front->getDestination())
                                       ->getTransmissionChannel()
                                       ->getTransmissionFinishTime();

            if (finishtime < simTime()) {
                EV_INFO << "sending packet" << endl;
                emit(sigQtime, simTime() - front->getEnqueued());
                send(front, "line$o", front->getDestination());
                front = nullptr;

                if (fifo.getLength() > 0) {  // fifo has packages
                    front = dynamic_cast<Packet *>(fifo.pop());

                    if (front->getDestination() !=
                        arbiterWait) {  // changing direction
                        requestArbitration(front->getSource(),
                                           front->getDestination());
                        granted = false;
                    }
                } else {
                    releaseArbitration(sourceWait, arbiterWait);
                }
            }
        }
        scheduleAt(simTime() + delay, msg);  // recheck in delay seconds

    } else if (msg->arrivedOn("in")) {
        if (dynamic_cast<Packet *>(msg) != nullptr) {
            EV_INFO << "storing" << endl;
            fifo.insert(msg);
        } else {
            // not a Packet throw it away
            EV_INFO << "got non packet message!" << endl;
            delete msg;
        }

        if (!waiting) {
            EV_INFO << "popping" << endl;
            front = dynamic_cast<Packet *>(fifo.pop());
            requestArbitration(front->getSource(), front->getDestination());
            waiting = true;
        }
    } else if (waiting && msg->arrivedOn("arbiterCtrl$i", arbiterWait)) {
        EV_INFO << "got a grant from arbiter "
                << dynamic_cast<Arbpkt *>(msg)->getSourcePort() << endl;
        if (dynamic_cast<Arbpkt *>(msg)->getSourcePort() == arbiterWait) {
            granted = true;
            waiting = false;
        } else {
            EV_INFO << "got a message from unexpected arbiter!" << endl;
        }
        delete msg;
    } else {
        EV_INFO << "got a message?!" << endl;
        delete msg;
    }
}
