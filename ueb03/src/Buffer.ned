package ueb03

simple Buffer {
    parameters:
        int size = default(0);
        double checkingDelay @unit(s) = default(10ms);
    gates:
        input data_in;
        output data_out;

        inout line;
}
