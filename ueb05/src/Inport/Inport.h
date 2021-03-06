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

#ifndef __exercise5_INPORT_H_
#define __exercise5_INPORT_H_

#include <omnetpp.h>
#include <vector>
#include "../Packets/Packet_m.h"
#include "../Packets/ReqGrant_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Inport : public cSimpleModule
{
  public:
    ~Inport();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  private:
    std::vector<bool> reqActive;
    std::vector<cQueue> buffer;
    std::vector<ReqGrant *> createRelease;

    simsignal_t qlen;
    simsignal_t qtime;
};

#endif
