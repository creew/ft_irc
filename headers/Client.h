#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <vector>
#include "ServerConfiguration.h"
#include "RawMessage.h"
#include "IServer.h"
#include "IClient.h"

enum ClientState {
    BODY,
    CR,
    LF
};

class Client : public IClient {
private:
    int fd;
    char *user;
    char *nick;
    char recvBuf[512];
    int recvBufLength;
    char state;
    IServer *server;
    std::vector<RawMessage *> sendQueue;

    void processCommand(char *buf);

public:
    int getFd() const {
        return fd;
    }

    Client(int fd, IServer *server);

    virtual ~Client();
    void processData(const char *data, int length);
    const char *getServerPassword();

    std::vector<RawMessage *> *getSendQueue() {
        return &sendQueue;
    }

    void setNick(char *const string);

    void setUser(char *user);

    char *getUser() const {
        return user;
    }

    char *getNick() const {
        return nick;
    }

    void pushMessage(RawMessage *outMessage);

    const char *getHostName();
};


#endif //FT_IRC_CLIENT_H
