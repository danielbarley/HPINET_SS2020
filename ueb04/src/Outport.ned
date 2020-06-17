package ueb04;

import ueb04.Mux;
import ueb04.Arbiter;
import ueb04.Outbuf;

module Outport
{
    parameters:
        int SIZE = default(4);

    gates:
        inout arbiterCtrl[SIZE];
        inout line[SIZE];
        output out;

    submodules:
        arbiter: Arbiter {
            SIZE = SIZE;
            @display("p=48,65");
        }
        mux: Mux {
            SIZE = SIZE;
            @display("p=48,137");
        }
        outbuf: Outbuf {

            @display("p=143,137");
        }
    connections:
        for i=0..SIZE-1 {
            arbiterCtrl[i] <--> arbiter.ctrl[i];
            in[i] <--> mux.in[i];
        }
        mux.out --> outbuf.in;
        outbuf.out --> out;
}
