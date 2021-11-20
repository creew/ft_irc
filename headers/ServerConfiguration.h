#ifndef FT_IRC_SERVERCONFIGURATION_H
#define FT_IRC_SERVERCONFIGURATION_H

#include <cstring>
#include <string>
#include <ostream>

class ServerConfiguration {
private:
    std::string host;
    int port_network;
    std::string password_network;
    int port;
    std::string password;

    static long parsePort(const std::string &sport);
public:
    bool isNetworkServerSet() {
        return !host.empty();
    }

    void parseConfiguration(int argc, char *argv[]);

    void parseNetworkArg(const std::string &network_arg);

    const std::string &getHost() const {
        return host;
    }

    int getPortNetwork() const {
        return port_network;
    }

    const std::string &getPasswordNetwork() const {
        return password_network;
    }

    int getPort() const {
        return port;
    }

    const std::string &getPassword() const {
        return password;
    }
};

#endif //FT_IRC_SERVERCONFIGURATION_H
