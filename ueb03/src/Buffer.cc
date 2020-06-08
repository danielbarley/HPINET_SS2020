#include "Buffer.h"

Define_Module(Buffer);

void Buffer::initialize() {
    fifo = cQueue("buffer_fifo");
    delay = static_cast<double>(par("checkingDelay"));
    scheduleAt(simTime(), new cMessage); // timer event for checking line$o
}

void Buffer::handleMessage(cMessage *msg) {
    simtime_t finishtime = gate("line$o")->getTransmissionChannel()->getTransmissionFinishTime();
    if (msg->isSelfMessage()) { // timer event to check for empty line
        if (finishtime < simTime() || fifo.getLength() > 0) { // line$o not busy and we have data stored
            EV_INFO << "sending out (timer event)\n";
            send(dynamic_cast<cMessage*>(fifo.pop()), "line$o");
        }
        scheduleAt(simTime() + delay, msg); // recheck in delay seconds

    } else if (msg->arrivedOn("data_in")) { // incoming msg from higher layer (to be buffered)
        if (finishtime < simTime()) {
            EV_INFO << "sending out (direct)\n";
            send(msg, "line$o");
        } else {
            EV_INFO << "line busy\n";
            if (static_cast<int>(par("size")) == 0 || fifo.getLength() < static_cast<int>(par("size"))) {
                EV_INFO << "storing msg in queue (line busy)\n";
                fifo.insert(msg);
            } else {
                EV_INFO << "dropping msg (Queue full)\n";
                delete msg;
            }
        }

    } else if (msg->arrivedOn("line$i")) { //incoming msg from datarate channel
        EV_INFO << "sending msg (to higher layer)\n";
        send(msg, "data_out");

    } else { // in case something unexpected arrives
        EV_INFO << "dropping msg (fall through)\n";
        delete msg;
    }
}
