//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "Inport.h"

Define_Module(Inport);

Inport::~Inport() {
    for (auto re: createRelease) {
        cancelAndDelete(re);
    }
    //delete buffer;
}

void Inport::initialize() {
    for (int virt = 0; virt < static_cast<int>(par("numPorts")); virt++) {
        buffer.push_back(cQueue(("PktStore" + std::to_string(virt)).c_str()));
        reqActive.push_back(false);
        createRelease.push_back(new ReqGrant("createRelease"));
    }

    qlen = registerSignal("qlen");
    qtime = registerSignal("qtime");

    gate("in")->setDeliverOnReceptionStart(par("cutThrough"));
}

void Inport::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("in")) {
        Packet *pkt = check_and_cast<Packet*>(msg);
        int dest = pkt->getDestination();
        if (!reqActive[dest]) {
            int src = pkt->getSource();
            std::stringstream ss;
            ss << "Req from " << src;
            ReqGrant *req = new ReqGrant(ss.str().c_str());

            req->setType(REQUEST);
            req->setOutports(dest);
            req->setSource(src);

            EV_INFO << "No Req outstanding. Generate Request to arbiter "
                           << dest << endl;
            send(req, "arbiterCtrl$o", dest);

            msg->setTimestamp();
            buffer[dest].insert(msg);

            //one packet is temporary stored, so "real" qsize is one less
            emit(qlen, buffer[dest].getLength());
            reqActive[dest] = true;
        } else {
            msg->setTimestamp();
            buffer[dest].insert(msg);
            EV_INFO << "Requests are outstanding. Queue Request" << endl;
            EV_INFO << "Request waiting: " << buffer[dest].getLength() << endl;
            //one packet is temporary stored, so "real" qsize is one less
            emit(qlen, buffer[dest].getLength());
        }
    } else if (msg->arrivedOn("arbiterCtrl$i")) {
        ReqGrant *rg = check_and_cast<ReqGrant*>(msg);
        if (rg->getType() != GRANT) {
            EV_ERROR << "Received something other than a grant in an inport!"
                            << std::endl;
        }
        Packet *pkt = check_and_cast<Packet *>(
            buffer[msg->getArrivalGate()->getIndex()].pop());
        emit(qtime, simTime() - pkt->getTimestamp());
        int dest = pkt->getDestination();

        EV_INFO << "Received Grant. Sending packet to outport=" << dest << endl;

        send(pkt, "outp", dest);
        simtime_t duration = pkt->getDuration();
        //simtime_t duration = gate("outp",dest)->getTransmissionChannel()->getTransmissionFinishTime();

        createRelease[dest]->setOutports(dest);

        EV_INFO << "Packet duration is: " << duration * 1000000 << "us" << endl;
        //EV_INFO << "Received Grant. Packet duration is: " << (duration - simTime()) * 1000000 << endl;

        scheduleAt(simTime() + duration, createRelease[dest]);
        delete msg;

        //one packet is temporary stored, so "real" qsize is one less
        emit(qlen, buffer[dest].getLength());
    } else {
        // self messages
        //if (msg == createRelease[]) {
        if (check_and_cast<ReqGrant *>(msg) != nullptr) {

            ReqGrant *rel = new ReqGrant("Release");

            //int dest = createRelease->getOutports();
            int dest = check_and_cast<ReqGrant *>(msg)->getOutports();

            EV_INFO << "Transfer complete. Send Release to arbiter= " << dest
                           << endl;

            rel->setType(RELEASE);
            rel->setOutports(dest);

            send(rel, "arbiterCtrl$o", dest);

            if (buffer[dest].isEmpty()) {
                reqActive[dest] = false;
                EV_INFO << "No Requests are waiting." << endl;

            } else {
                //outstanding requests in buffer
                Packet *pkt = check_and_cast<Packet*>(buffer[dest].front());
                int dest = pkt->getDestination();
                int src = pkt->getSource();
                std::stringstream ss;
                ss << "Req from " << src;
                ReqGrant *req = new ReqGrant(ss.str().c_str());

                req->setType(REQUEST);
                req->setOutports(dest);
                req->setSource(src);

                EV_INFO  << "Req are outstanding. Generate new Request to arbiter="
                         << dest << " from queue" << endl;

                send(req, "arbiterCtrl$o", dest);
                reqActive[dest] = true;
            }
        }
    }
}
