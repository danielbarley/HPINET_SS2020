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

// Created: 2020-4-11 for project ueb01

package packettest.simulations;

import packettest.Simple2;
import ned.DelayChannel;

//
// A generated network with ring topology.
//
network Network2
{
    submodules:
        tic: Simple2 {
            @display("p=200,50");
            TIC = true;
        }
        toc0: Simple2 {
            @display("p=342,154");
            
        }
        toc1: Simple2 {
            @display("p=288,322");
            
        }
        toc2: Simple2 {
            @display("p=111,322");
            
        }
        toc3: Simple2 {
            @display("p=57,154");
            
        }
    connections:
        tic.next <--> DelayChannel <--> toc0.prev;
        toc0.next <--> DelayChannel <--> toc1.prev;
        toc1.next <--> DelayChannel <--> toc2.prev;
        toc2.next <--> DelayChannel <--> toc3.prev;
        toc3.next <--> DelayChannel <--> tic.prev;
}
