package ueb04;

simple Inport {
    parameters:
        int SIZE = default(4);
        double checkingDelay @unit(s)= default(1us);
        @signal[sigQlength](type=long);
        @signal[sigQtime](type=double);
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
