package ueb04;

simple Mux {
    parameters:
        int SIZE = default(4);

    gates:
        inout in[SIZE];
        output out;
}
