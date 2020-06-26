package exercise5.App;

simple App
{
    parameters:
        int nodeID;
        int numNodes;
        bool cutThrough = default(false);
        volatile double sendInterval @unit(s) = default(uniform(1us,10us));
        volatile int pktSize = default(64 * intuniform(1,64));
        
        @signal[sent](type = Packet);
        @signal[rcvd](type = Packet);
        @signal[eed](type = simtime_t);
        @statistic[sentCnt](source=count(sent); record=last,vector?);
        @statistic[rcvdCnt](source=count(rcvd); record=last,vector?);
        @statistic[packetSize](source=packetBits(sent); record=min,max,mean,histogram,stats,vector?);
        @statistic[rcvdBits](source=sumPerDuration(packetBits(rcvd))/1000000; record=last);
        @statistic[endToEndDelay](source=eed; record=min,max,vector,timeavg);
        
        
    gates:
        input in;
        output out;
}
