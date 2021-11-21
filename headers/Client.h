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

    bool processCommand(char *buf);

public:
    int getFd() const {
        return fd;
    }

    Client(int fd, IServer *server);

    virtual ~Client();
    bool processData(const char *data, size_t length);
    const char *getServerPassword();

    std::vector<RawMessage *> *getSendQueue() {
        return &sendQueue;
    }

    void setNick(const char *string);

    void setUser(const char *user);

    char *getUser() const {
        return user;
    }

    char *getNick() const {
        return nick;
    }

    void pushMessage(RawMessage *outMessage);

    const char *getHostName();

    std::vector<Channel *> getChannels() {
        return server->getChannels();
    }
};


#endif //FT_IRC_CLIENT_H
