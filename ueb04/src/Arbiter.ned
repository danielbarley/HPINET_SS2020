package ueb04;

simple Arbiter {
    parameters:
        int SIZE = default(4);

    gates:
        inout ctrl[SIZE];
}
