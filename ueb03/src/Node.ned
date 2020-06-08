package ueb03;

module Node
{
	gates:
		inout line;
	submodules:
		app : App;
		buffer : Buffer;
	connections:
		app.in <-- buffer.out;
		app.out --> buffer.in;
		buffer.line <--> line;
}
