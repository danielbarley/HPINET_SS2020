package ueb04;

simple Inport {
    parameters:
        int SIZE = default(4);
        int checkingDelay @unit(s)= default(1us);

    gates:
        input in;
        inout line[SIZE];
        inout arbiterCtrl[SIZE];
}
