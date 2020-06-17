package ueb04;

simple Inport {
    parameters:
        int SIZE = default(4);

    gates:
        input in;
        inout line[SIZE];
        inout arbiterCtrl[SIZE];
}
