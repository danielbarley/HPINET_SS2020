package ueb02;

simple App
{
    parameters:
        int nodeID;
        volatile double sendDelay @unit(s) = uniform(1.0us, 10.0us);

    gates:
        input data_in;
        output data_out;
}
