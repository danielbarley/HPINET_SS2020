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

#include "Mux.h"

Define_Module(Mux);

void Mux::initialize()
{
    // TODO - Generated method body

    for (int i = 0; i < gateSize("inp"); i++) {
        gate("inp",i)->setDeliverOnReceptionStart(par("cutThrough"));
    }
}

void Mux::handleMessage(cMessage *msg)
{
    send(msg,"out");
}
