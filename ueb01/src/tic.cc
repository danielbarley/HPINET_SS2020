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
//

//#include <memory>

#include "tic.h"

Define_Module(Tic);

void Tic::initialize()
{
    //std::shared_ptr<cMessage> selfmsg = std::make_shared<cMessage>("Timer");
    //cMessage * selfmsg = new cMessage("Timer");
    //scheduleAt(simTime(), selfmsg);
    cPacket *dataPkt = new cPacket("Tic");
    dataPkt->setByteLength(par("PKT_SIZE"));
    send(dataPkt, "data$o");
}

void Tic::handleMessage(cMessage *msg)
{
    delete msg;

    cPacket *dataPkt = new cPacket("Tic");
    dataPkt->setByteLength(par("PKT_SIZE"));
    send(dataPkt, "data$o");
}
