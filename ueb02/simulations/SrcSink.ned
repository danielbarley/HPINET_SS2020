package ueb02.simulations;

import ueb02.App;
import ned.DelayChannel;

network SrcSink {
    parameters:
        double CHANNEL_DELAY @unit(s) = default(1ms);
        int NUM_NODES = default(2);


    types:
        channel C extends ned.DelayChannel {
            delay = CHANNEL_DELAY;
        }

    submodules:
        App[NUM_NODES]: App;

    connections:
        for i = 0..NUM_NODES-2 {
            App[i].data_out --> App[i+1].data_in;
        }
        App[NUM_NODES-1].data_out --> App[0].data_in;
}
