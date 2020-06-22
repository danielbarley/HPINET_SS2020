package ueb04.simulations;

import ueb04.Node;
import ueb04.XBar;

network NetXBar
{
    parameters:
		double DATA_RATE @unit(Gbps) = default(1Gbps);
        //int NUM_NODES = default(4);
        int NUM_NODES = 4;
	types:
		channel C extends ned.DatarateChannel {
            datarate = DATA_RATE;
		}
    submodules:
        node[NUM_NODES]: Node {
            nodeID = index;
            numNodes = NUM_NODES;
        };
        xbar: XBar {};

    connections:
        for i=0..NUM_NODES-1 {
            node[i].line$o --> C --> xbar.in[i];
            xbar.out[i] --> C --> node[i].line$i;
        }
}
