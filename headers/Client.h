#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <vector>
#include "ServerConfiguration.h"
#include "RawMessage.h"
#include "Server.h"
#include "Client.h"

enum ClientState {
    BODY,
    CR,
    LF
};

class ChannelHandler;
class Server;
class Client {
private:
    int fd;
    char *user;
    char *nick;
    char recvBuf[512];
    int recvBufLength;
    char state;
    Server *server;
    ChannelHandler *channelHandler;
    std::vector<RawMessage *> sendQueue;

    bool processCommand(char *buf);

public:
    int getFd() const;

    ChannelHandler *getChannelHandler() const;

    Client(int fd, Server *server, ChannelHandler *channelHandler);

    virtual ~Client();
    bool processData(const char *data, size_t length);
    const char *getServerPassword();

    void setNick(const char *string);

    void setUser(const char *user);

    char *getUser() const;

    char *getNick() const;

    void pushMessage(RawMessage *outMessage);

    const char *getHostName();

    void sendMessages();
};


#endif //FT_IRC_CLIENT_H
