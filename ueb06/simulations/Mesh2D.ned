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

// Created: 2020-6-15 for project ueb06

package ss2020_ueb06.simulations;

import ss2020_ueb06.Node.Node;
import ned.DatarateChannel;

//
// A generated network with grid topology.
//
network Mesh2D
{
    parameters:
        int columns = default(4);
        int rows = default(4);
    submodules:
        node[columns*rows]: Node {
            @display("p=50,50,m,4,75,75");
            gates:
                data[4];
        }
    connections allowunconnected:
        for i=0..rows-1, for j=0..columns-2 {
            node[i*columns+j].data[1] <--> DatarateChannel <--> node[i*columns+j+1].data[0] if j!=columns-1;
            node[i*columns+j].flowCtrl[1] <--> DatarateChannel <--> node[(i+1)*columns+j].flowCtrl[0] if i!=rows-1;
        }
        for i=0..rows-2, for j=0..columns-1 {
            node[i*columns+j].data[3] <--> DatarateChannel <--> node[(i+1)*columns+j].data[2] if i!=rows-1;
            node[i*columns+j].flowCtrl[3] <--> DatarateChannel <--> node[(i+1)*columns+j].flowCtrl[2] if i!=rows-1;
        }
}
