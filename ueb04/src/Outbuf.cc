#include "Outbuf.h"
#include "packet_m.h"

Define_Module(Outbuf);

void Outbuf::initialize() {
    fifo = cQueue("outport_buffer");
    delay = static_cast<double>(par("checkingDelay"));
    sigQlength = registerSignal("sigQlength");
    sigQtime = registerSignal("sigQtime");

    scheduleAt(simTime(), new cMessage);
}

void Outbuf::handleMessage(cMessage *msg) {
    emit(sigQlength, fifo.getLength());
    if (msg->isSelfMessage()) {
        simtime_t finishtime = gate("out")
                                   ->getTransmissionChannel()
                                   ->getTransmissionFinishTime();

        if (fifo.getLength() > 0 && finishtime < simTime()) {
            Packet * nmsg = dynamic_cast<Packet *>(fifo.pop());
            emit(sigQtime, simTime() - nmsg->getEnqueued());
            send(nmsg, "out");
        }
        scheduleAt(simTime() + delay, msg);
    } else if (msg->arrivedOn("in")) {
        dynamic_cast<Packet *>(msg)->setEnqueued(simTime());
        fifo.insert(msg);
    } else {
        delete msg;
    }
}
