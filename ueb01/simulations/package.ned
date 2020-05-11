package packettest.simulations;

import packettest.Simple;
import packettest.Simple2;
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

network ueb01_3
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
