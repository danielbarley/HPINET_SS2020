package ueb04;

simple Buffer
{
    parameters:
        int size = default(0);
        double checkingDelay @unit(s) = default(100ns);

        @signal[sigNumInQueue](type=long);
        @signal[sigTimeInQueue](type=simtime_t);
        @signal[sigNumDiscarded](type=bool);
        @signal[sigBusyLine](type=bool);

        @statistic[statNumInQueue](
            title="Number of Packets waiting";
            source=sigNumInQueue;
            record=vector;
        );
        @statistic[statTimeInQueue](
            title="Time of wait in Queue";
            source=sigTimeInQueue;
            record=vector;
        );
        @statistic[statNumDiscarded](
            title="Number of Packets Discarded";
            source=count(sigNumDiscarded);
            record=vector;
        );
        @statistic[statBusyLine](
            title="State of Line";
            source=sigBusyLine;
            record=vector;
        );
    gates:
        input data_in;
        output data_out;

        inout line;
}
