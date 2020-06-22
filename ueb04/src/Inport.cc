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
#include "packet_m.h"
#include "arbpkt_m.h"

Define_Module(Inport);

void Inport::initialize() {
    fifo = cQueue("inport_buffer");
    delay = static_cast<double>(par("checkingDelay"));
    scheduleAt(simTime(), new cMessage); // timer event for checking line$o

    sigQlength = registerSignal("sigQlength");
    sigQtime = registerSignal("sigQtime");
}

void Inport::handleMessage(cMessage *msg) {
    emit(sigQlength, fifo.getLength());
    if (msg->isSelfMessage()) { //timer interval and we can send
        if (granted) {
            simtime_t finishtime = gate("line$o", front->getDestination())->getTransmissionChannel()->getTransmissionFinishTime();
            if (finishtime < simTime()) {
                EV_INFO << "sending packet" << endl;
            	send(front, "line$o", front->getDestination());
				if (fifo.getLength() > 0) { // fifo has packages
					front = dynamic_cast<Packet *>(fifo.pop());
					if (front->getDestination() != arbiterWait) { // changing direction
						Arbpkt * req = new Arbpkt();
						req->setType(0);
						req->setSourcePort(front->getSource());
						req->setTargetOutport(front->getDestination());
						send(req, "arbiterCtrl$o", front->getDestination());
						granted = false;
						arbiterWait = front->getDestination();
						sourceWait = front->getSource();
					}
				} else {
					Arbpkt * rel = new Arbpkt();
					rel->setType(2);
					rel->setTargetOutport(arbiterWait);
					rel->setSourcePort(sourceWait);
					EV_INFO << "releasing grant from arbiter " << arbiterWait << endl;
					send(rel, "arbiterCtrl$o", front->getDestination());
					granted = false;
				}
            }
        }
        scheduleAt(simTime() + delay, msg); // recheck in delay seconds
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
            EV_INFO << "requesting  for arbiter "<< front->getDestination() << endl;
            Arbpkt * req = new Arbpkt();
            req->setType(0);
            req->setSourcePort(front->getSource());
            req->setTargetOutport(front->getDestination());
            waiting = true;
            arbiterWait = front->getDestination();
            send(req, "arbiterCtrl$o", front->getDestination());
            EV_INFO << "waiting" << endl;
        }
    } else if (waiting && msg->arrivedOn("arbiterCtrl$i")) {
        EV_INFO << "got a grant from arbiter " << dynamic_cast<Arbpkt *>(msg)->getSourcePort() << endl;
        if (dynamic_cast<Arbpkt *>(msg)->getSourcePort() == arbiterWait) {
            granted = true;
            waiting = false;
        } else {
            EV_INFO << "got a message from unexpected arbiter!" << endl;
            delete msg;
        }
    } else {
        EV_INFO << "got a message on a not defined gate!" << endl;
        delete msg;
    }
}
