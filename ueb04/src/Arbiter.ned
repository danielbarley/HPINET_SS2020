package ueb04;

simple Arbiter {
    parameters:
        int SIZE = default(4);
        double checkingDelay @unit(s) = default(100ns);

        @signal[sigOutstandingRequests](type=long);
        @signal[sigServiceTime](type=simtime_t);

        @statistic[statOutstandingRequests](
            title="Length of Queue";
            source=sigOutstandingRequests;
            record=vector;
        );
        @statistic[statServiceTime](
            title="Time in Queue";
            source=sigServiceTime;
            record=vector;
        );

    gates:
        inout ctrl[SIZE];
}
