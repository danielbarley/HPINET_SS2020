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

Define_Module(Inport);

void Inport::initialize() {
    fifo = cQueue("inport_buffer");
    delay = static_cast<double>(par("checkingDelay"));
    scheduleAt(simTime(), new cMessage); // timer event for checking line$o
}

void Inport::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() && granted) { //timer interval and we can send
        send(front, "line$o", front->destination);
        if (fifo.length() > 0) { // fifo has packages
            front = dynamic_cast<Packet *>(fifo.pop());
            if (front->destination != arbiterWait) { // changing direction
                cMessage * req = new cMessage();
                send(req, "arbiterCtrl$o", front->destination);
                granted = false;
            }
        } else {
            cMessage * req = new cMessage();
            send(req, "arbiterCtrl$o", front->destination);
            granted = false;
        }
        scheduleAt(simTime() + delay, msg); // recheck in delay seconds
    } else if (msg->arrivedOn("in")) {
        if (dynamic_cast<Packet *>(msg) != nullptr) {
            fifo.insert(msg);
        } else {
            // not a Packet throw it away
            EV_INFO << "got non packet message!" << endl;
            delete msg
        }

        if (!waiting) {
            front = dynamic_cast<Packet *>(fifo.pop());
            cMessage * req = new cMessage();
            send(req, "arbiterCtrl$o", front->destination);
            waiting = true;
            arbiterWait = front->destination;
        }
    } else if (waiting) {
        if (msg->arrivedOn("arbiterCtrl$i", arbiterWait)) {
            EV_INFO << "got a grant from arbiter " << arbiterWait << endl;
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
