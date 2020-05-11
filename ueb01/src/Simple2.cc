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

#include "Simple2.h"
#include "MyPacket_m.h"

Define_Module(Simple2);

void Simple2::send_random(cMessage* msg) {
    bool next = static_cast<bool>(intuniform(0,1));
    if (next) {
        send(msg, "next$o");
     }
     else {
         send(msg, "prev$o");
     }
}

void Simple2::initialize()
{
    cnt = 0;
    if ( static_cast<bool>(par("TIC")) ) {
            cPacket *dataPkt = new cPacket("msg");
            dataPkt->setByteLength(par("PKT_SIZE"));
            send(dataPkt, "next$o");
        }
}

void Simple2::handleMessage(cMessage *msg)
{
    if (static_cast<bool>(par("TIC"))){
        cnt++;
        if (cnt < 6) {
            send_random(msg);
        }
        else {
            delete msg;
            cPacket *dataPkt = new cPacket("msg");
            dataPkt->setByteLength(par("PKT_SIZE"));
            send(dataPkt, "next$o");
        }
    }
    else {
        send_random(msg);
    }
}
