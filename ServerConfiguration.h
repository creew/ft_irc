//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_SERVERCONFIGURATION_H
#define FT_IRC_SERVERCONFIGURATION_H

#include <cstring>
#include <string>

typedef struct Configuration {
    std::string host;
    int port_network;
    std::string password_network;
    int port;
    std::string password;
} SConfiguration;

class ServerConfiguration {
public:
    Configuration parseConfiguration();
};

#endif //FT_IRC_SERVERCONFIGURATION_H
