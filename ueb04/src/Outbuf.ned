package ueb04;

simple Outbuf {
    parameters:
        double checkingDelay @unit(s) = default(100ns);
    gates:
        input in;
        output out;
}
