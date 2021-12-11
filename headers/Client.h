#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <vector>
#include "ServerConfiguration.h"
#include "RawMessage.h"
#include "Server.h"
#include "Client.h"
#include "UserHandler.h"

enum ClientState {
    BODY,
    CR,
    LF
};

class ChannelHandler;
class UserHandler;
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
    std::vector<RawMessage *> sendQueue;
    bool isOp;
    string ip;


    bool processCommand(char *buf);

public:
    int getFd() const;

    Client(int fd, Server *server, char *ip);

    virtual ~Client();


    /**
     * Returns true if need to disconnect user
     */
    bool processData(const char *data, size_t length);

    const char *getServerPassword();

    void setNick(const char *string);

    void setUser(const char *user);

    char *getUser() const;

    char *getNick() const;

    const string &getIp() const {
        return ip;
    }

    void pushMessage(RawMessage *outMessage);

    const char *getHostName();

    void sendMessages();

    ChannelHandler *getChannelHandler() const;

    UserHandler *getUserHandler() const;
};


#endif //FT_IRC_CLIENT_H
