//
// Created by Алексей on 14.11.2021.
//

#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <vector>
#include "ServerConfiguration.h"
#include "OutMessage.h"

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
    char state;
    const Configuration *serverConfiguration;
    std::vector<OutMessage *> sendQueue;
public:
    int getFd() const;

    Client(int fd, const Configuration *serverConfiguration);
    virtual ~Client();
    void processData(const char *data, int length);
    const char *getServerPassword();
    void processCommand(char *buf);

    std::vector<OutMessage *> *getSendQueue() {
        return &sendQueue;
    }

    void sendRplWelcome();
    void sendErrNeedMoreParams(const char *command);

    void setNick(char *const string);

    void setUser(char *user);

    void sendRplYourHost();

    void sendRplCreated();

    void sendRplMyInfo();

    void sendPong();
};


#endif //FT_IRC_CLIENT_H
