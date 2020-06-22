package ueb04;

import ueb04.Outport;

module XBar
{
    parameters:
        int SIZE = default(4);
        double DATA_RATE @unit(Gbps) = default(1Gbps);
    gates:
        input in[SIZE];
        output out[SIZE];
    types:
        channel C extends ned.DatarateChannel
        {
            datarate = DATA_RATE;
        }
    submodules:
        inports[SIZE]: Inport {
            SIZE = SIZE;
            @display("p=50,62");
        }
        outports[SIZE]: Outport {
            SIZE = SIZE;
            @display("p=177,62");
        }

    connections:
        for i=0..SIZE-1, for j=0..SIZE-1 {
            inports[i].line[j] <--> C <--> outports[i].line[j]; // All to All
            inports[i].arbiterCtrl[j] <--> { @display("ls=,1,da"); } <--> outports[j].arbiterCtrl[i]; //Arbiter
        }
        for i=0..SIZE-1 {
            in[i] --> inports[i].in;
            outports[i].out --> out[i];
        }

}
