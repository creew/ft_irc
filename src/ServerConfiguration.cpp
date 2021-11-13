//
// Created by Edythe Klompus on 11/13/21.
//
#include <cstring>
#include "ServerConfiguration.h"

const Configuration &ServerConfiguration::getConfiguration() const {
    return configuration;
}

// [host:port_network:password_network] <port> <password>
void ServerConfiguration::parseConfiguration(int argc, char **argv) {
    int i = 1;
    char *end;

    if (argc != 3 && argc != 4) {
        throw std::invalid_argument("usage: ./ircserv [host:port_network:password_network] <port> <password>");
    }
    if (argc == 4) {
        std::string network_arg = argv[i++];

        size_t nhost_pos = network_arg.find(':');
        if (nhost_pos == std::string::npos) {
            throw std::invalid_argument("usage: ./ircserv [host:port_network:password_network] <port> <password>");
        }
        configuration.host = network_arg.substr(0, nhost_pos);

        size_t nport_pos = network_arg.find(':', nhost_pos + 1);
        if (nport_pos == std::string::npos) {
            throw std::invalid_argument("usage: ./ircserv [host:port_network:password_network] <port> <password>");
        }

        long port = strtol(network_arg.substr(nhost_pos + 1, nport_pos - (nhost_pos + 1)).c_str(), &end, 10);
        if (*end != '\0' || port < 0 || port > 65535) {
            throw std::invalid_argument("usage: ./ircserv [host:port_network:password_network] <port> <password>\n"
                                        "   port_network must be positive number less 65535");
        }
        configuration.port_network = static_cast<int>(port);
        configuration.password_network = network_arg.substr(nport_pos + 1);
    }
    std::string sport = argv[i++];
    long port = strtol(sport.c_str(), &end, 10);
    if (*end != '\0' || port < 0 || port > 65535) {
        throw std::invalid_argument("usage: ./ircserv [host:port_network:password_network] <port> <password>\n"
                                    "   port must be positive number less 65535");
    }
    configuration.port = static_cast<int>(port);
    configuration.password = argv[i];
}
