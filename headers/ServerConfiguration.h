//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_SERVERCONFIGURATION_H
#define FT_IRC_SERVERCONFIGURATION_H

#include <cstring>
#include <string>
#include <ostream>

struct Configuration {
    std::string host;
    int port_network;
    std::string password_network;
    int port;
    std::string password;
};

class ServerConfiguration {
private:
    Configuration configuration;

    static long getPort(const std::string &sport);
public:
    const Configuration *getConfiguration() const;

    void parseConfiguration(int argc, char *argv[]);

    void parseNetworkArg(const std::string &network_arg);
};

#endif //FT_IRC_SERVERCONFIGURATION_H
