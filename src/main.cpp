#include <iostream>
#include "Server.h"
#include "ServerConfiguration.h"

char stopAll = 0;

void intHandler(int dummy) {
    stopAll = 1;
}

int main(int argc, char** argv) {
    Server *server = nullptr;
    signal(SIGINT, intHandler);
    ServerConfiguration serverConfiguration;
    try {
        serverConfiguration.parseConfiguration(argc, argv);
        server = new Server(&serverConfiguration);
        server->start();
    } catch (std::invalid_argument& e) {
        delete server;
        std::cerr << e.what();
        return (-1);
    }
    return 0;
}
