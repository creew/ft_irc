#include <iostream>
#include "Server.h"
#include "ServerConfiguration.h"

int main(int argc, char** argv) {
    Server *server = nullptr;
    ServerConfiguration serverConfiguration;
    try {
        serverConfiguration.parseConfiguration(argc, argv);
        server = new Server(&serverConfiguration);
        server->start();
    } catch (std::invalid_argument& e) {
        delete server;
        std::cerr << e.what() << std::endl;
        return (-1);
    }
    return 0;
}
