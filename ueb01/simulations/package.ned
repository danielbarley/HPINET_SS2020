package packettest.simulations;

import packettest.Tic;
import packettest.Toc;
import ned.DelayChannel;

network Testnet {
    parameters:
        int PKT_SIZE_NET @unit(byte) = default(512Byte);
        double DATA_RATE_NET @unit(bps) = default(1Gbps);
        double CHANNEL_DELAY @unit(s) = default(100ns);

    types:
        channel C extends ned.DelayChannel {
            delay = CHANNEL_DELAY;
        }

    submodules:
        node0: Tic {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
        }

        node1: Toc {
            PKT_SIZE = PKT_SIZE_NET;
            DATA_RATE = DATA_RATE_NET;
        }

    connections:
        node0.data<-->C<-->node1.data;
}
