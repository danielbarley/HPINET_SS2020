package ueb04;

simple Arbiter {
    parameters:
        int SIZE = default(4);
        double checkingDelay @unit(s) = default(100ns);

    gates:
        inout ctrl[SIZE];
}
