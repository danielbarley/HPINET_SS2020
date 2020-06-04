package ueb03;

simple App
{
    parameters:
        int nodeID;
        int numNodes;
        volatile double sendDelay @unit(s) = uniform(1.0us, 10.0us);
        @signal[sigPacketReceived](type=bool);
        @signal[sigPacketReceivedSize](type=long);
        @signal[sigPacketSent](type=bool);
        @statistic[statPacketsReceived](
            title="Packets Received";
            source=count(sigPacketReceived);
            record=vector;
        );
        @statistic[statPacketsReceivedSize](
            title="Size of Packets Received";
            source=sigPacketReceivedSize;
            record=vector;
        );
        @statistic[statPacketsSent](
            title="Packets Sent";
            source=count(sigPacketReceived);
            record=vector;
        );
    gates:
        input data_in;
        output data_out;
}
