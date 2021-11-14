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
    char *user;
    char *nick;
    char recvBuf[512];
    int recvBufLength;
    char sendBuf[512];
    int sendBufLength;
    char state;
    const Configuration *serverConfiguration;

public:
    int getFd() const;

    Client(int fd, const Configuration *serverConfiguration);
    virtual ~Client();
    void processData(const char *data, int length);
    const char *getServerPassword();
    void processCommand(char *buf);
    void sendRplWelcome();
    void sendErrNeedMoreParams(const char *command);

    void setNick(char *const string);

    void setUser(char *user);

    void sendRplYourHost();

    void sendRplCreated();

    void sendRplMyInfo();
};


#endif //FT_IRC_CLIENT_H
