packet Arbpkt {
    unsigned int type;
    int sourcePort;
    int targetOutport;
    simtime_t enqueued;
}
