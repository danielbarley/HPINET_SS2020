package ueb04;

simple Inport {
    parameters:
        int SIZE = default(4);
        double checkingDelay @unit(s)= default(100ns);
        @signal[sigQlength](type=long);
        @signal[sigQtime](type=simtime_t);
		@statistic[statQlength](
            title="Average number of buffered packets";
            source=sigQlength;
            record=mean;
        );
        @statistic[statQtime](
            title="Average time spent in buffer";
            source=sigQtime;
            record=mean;
        );
    gates:
        input in;
        inout line[SIZE];
        inout arbiterCtrl[SIZE];
}
