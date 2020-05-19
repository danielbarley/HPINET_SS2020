#include "App.h"

Define_Module(App);

void App::initialize() {
    nodeID = static_cast<int>(par("nodeID"));
    sendDelay = static_cast<double>(par("sendDelay"));
}

void App::handleMessage(cMessage *msg) {
    delete msg;
}
