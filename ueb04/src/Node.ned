package ueb04;

import ueb04.App;
import ueb04.Buffer;

module Node
{
    parameters:
        int nodeID;
        int numNodes;
    gates:
        inout line;
    submodules:
        app: App {
            @display("p=26,60");
            numNodes = numNodes;
            nodeID = nodeID;
        }
        buffer: Buffer {
            @display("p=92,60");
        }
    connections:
        app.data_in <-- buffer.data_out;
        app.data_out --> buffer.data_in;
        buffer.line <--> line;
}
