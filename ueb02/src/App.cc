#include "App.h"

Define_Module(App);

void App::initialize() {
    //nodeID = this->getId();
    sendDelay = par("sendDelay");
}

void App::handleMessage(cMessage *msg) {
    delete msg;
}
