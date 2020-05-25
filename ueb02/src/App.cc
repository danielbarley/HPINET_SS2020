#include "App.h"
#include "packet_m.h"

Define_Module(App);

void App::initialize() {
    nodeID = static_cast<int>(par("nodeID"));
    sendDelay = static_cast<double>(par("sendDelay"));
    numNodes = static_cast<int>(par("numNodes"));
    scheduleAt(simTime(), new cMessage);
}

void App::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // schedule new self message for clocking and also send packet to random
        int destination = intuniform(0, numNodes - 1);
        int64_t packetLength = intuniform(1, 64) * 64; // bytes
        Packet *pkt = new Packet;
        pkt->setDestination(destination);
        pkt->setBitLength(packetLength);
        send(pkt, "data_out");
        scheduleAt(simTime() + sendDelay, msg);
    } else {
        // not a self message make sure it's a Packet
        if (dynamic_cast<Packet *>(msg) != nullptr) {
            EV_INFO << "NodeID " << nodeID << " got a Packet ";
            Packet *pkt = (Packet *) msg;
            if (pkt->getDestination() == nodeID) {
                EV_INFO << "and it was for me" << endl;
                delete msg;
            } else {
                EV_INFO << "but it was not for me sending to next node" << endl;
                send(pkt, "data_out");
            }
        } else {
            // not a Packet throw it away
            EV_INFO << "got non packet message!" << endl;
            delete msg;
        }
    }
}
