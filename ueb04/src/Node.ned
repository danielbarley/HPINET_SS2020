package ueb04;

import ueb04.App;
import ueb04.Buffer;

module Node
{
    gates:
        inout line;
    submodules:
        app: App {
            @display("p=26,60");
            numNodes = 2;
        }
        buffer: Buffer {
            @display("p=92,60");
        }
    connections:
        app.data_in <-- buffer.data_out;
        app.data_out --> buffer.data_in;
        buffer.line <--> line;
}
