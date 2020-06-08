package ueb03.simulations;

import ueb03.App;
import ueb03.Buffer;
import ueb03.Node;
import ned.DelayChannel;

network Net2 {
	parameters:
		double CHANNEL_DELAY @unit(s) = default(5us);
		double DATA_RATE @unit(Gbps) = default(1Gbps);

	types:
		channel C extends ned.DelayChannel {
			delay = CHANNEL_DELAY;
		}

	submodules:
		node0 : Node;
		node1 : Node;

	connections:
		node0.line <--> C <--> node1.line;
}
