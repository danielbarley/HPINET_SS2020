package packettest.simulations;

import packettest.Simple;
import ned.DelayChannel;

network ueb01_1 {
    parameters:
        int PKT_SIZE_NET @unit(byte) = default(512Byte);
        double DATA_RATE_NET @unit(bps) = default(1Gbps);
        double CHANNEL_DELAY @unit(s) = default(100ns);
        int NUM_DISCARD_NET = default(0);

    types:
        channel C extends ned.DelayChannel {
            delay = CHANNEL_DELAY;
        }

    submodules:
        tic: Simple {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
            NUM_DISCARD = NUM_DISCARD_NET;
            TIC = true;
        }

        toc: Simple {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
        }

    connections:
        tic.data<-->C<-->toc.data;
}

network ueb01_3 {
    parameters:
        int PKT_SIZE_NET @unit(byte) = default(512Byte);
        double DATA_RATE_NET @unit(bps) = default(1Gbps);
        double CHANNEL_DELAY @unit(s) = default(100ns);

    types:
        channel C extends ned.DelayChannel {
            delay = CHANNEL_DELAY;
        }

    submodules:
        tic: Simple {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
            TIC = true;
        }

        toc: Simple {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
        }

    connections:
        tic.data <--> C <--> toc.data;
}
