//
// Created by Алексей on 14.11.2021.
//

#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include "ServerConfiguration.h"

enum ClientState {
    BODY,
    CR,
    LF
};

class Client {
private:
    int fd;
    char *username;
    char buf[512];
    int bufLength;
    char state;
    const Configuration *serverConfiguration;
public:
    int getFd() const;

    Client(int fd, const Configuration *serverConfiguration);
    virtual ~Client();
    void processData(const char *data, int length);

    void processCommand(char buf[512]);
};


#endif //FT_IRC_CLIENT_H
