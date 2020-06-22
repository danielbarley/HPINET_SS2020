#include "Buffer.h"
#include "packet_m.h"

Define_Module(Buffer);

void Buffer::initialize() {
    fifo = cQueue("buffer_fifo");
    delay = static_cast<double>(par("checkingDelay"));
    scheduleAt(simTime(), new cMessage); // timer event for checking line$o
    //
    //register stats
    sigBusyLine = registerSignal("sigBusyLine");
    sigNumInQueue = registerSignal("sigNumInQueue");
    sigNumDiscarded = registerSignal("sigNumDiscarded");
    sigTimeInQueue = registerSignal("sigTimeInQueue");
    emit(sigNumInQueue, fifo.getLength());
}

void Buffer::handleMessage(cMessage *msg) {
    simtime_t finishtime = gate("line$o")->getTransmissionChannel()->getTransmissionFinishTime();
    if (msg->isSelfMessage()) { // timer event to check for empty line
        if (finishtime < simTime()) {
            if (fifo.getLength() > 0) { // line$o not busy and we have data stored
                EV_INFO << "sending out (timer event)\n";
                Packet* nmsg = dynamic_cast<Packet*>(fifo.pop());
                emit(sigNumInQueue, fifo.getLength());
                emit(sigTimeInQueue, simTime() - nmsg->getEnqueued());
                send(nmsg, "line$o");
            }
            emit(sigBusyLine, false);
        } else {
            emit(sigBusyLine, true);
        }
        scheduleAt(simTime() + delay, msg); // recheck in delay seconds

    } else if (msg->arrivedOn("data_in")) { // incoming msg from higher layer (to be buffered)
        if (finishtime < simTime()) {
            EV_INFO << "sending out (direct)\n";
            send(msg, "line$o");
            emit(sigTimeInQueue, simTime() - simTime());
        } else {
            EV_INFO << "line busy\n";
            if (static_cast<int>(par("size")) == 0 || fifo.getLength() < static_cast<int>(par("size"))) {
                EV_INFO << "storing msg in queue (line busy)\n";
                dynamic_cast<Packet *>(msg)->setEnqueued(simTime());
                fifo.insert(msg);
                emit(sigNumInQueue, fifo.getLength());
                emit(sigNumDiscarded, false);
            } else {
                EV_INFO << "dropping msg (Queue full)\n";
                delete msg;
                emit(sigNumDiscarded, true);
            }
        }

    } else if (msg->arrivedOn("line$i")) { //incoming msg from datarate channel
        EV_INFO << "sending msg (to higher layer)\n";
        send(msg, "data_out");

    } else { // in case something unexpected arrives
        EV_INFO << "dropping msg (fall through)\n";
        delete msg;
        emit(sigNumDiscarded, true);
    }
}
