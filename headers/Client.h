#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <vector>
#include <queue>
#include "ServerConfiguration.h"
#include "messages/RawMessage.h"
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
    string user;
    string nick;
    string realName;
    string host;
    char recvBuf[512];
    int recvBufLength;
    char state;
    Server *server;
    std::queue<RawMessage *> sendQueue;
    bool opMode;
    bool processCommand(char *buf);

public:
    int getFd() const;

    Client(int fd, Server *server, char *host);

    virtual ~Client();


    /**
     * Returns true if need to disconnect user
     */
    bool processData(const char *data, size_t length);

    const string & getServerPassword();

    const string &getUser() const {
        return user;
    }

    void setUser(const string &user) {
        Client::user = user;
    }

    const string &getNick() const {
        return nick;
    }

    void setNick(const string &nick) {
        Client::nick = nick;
    }

    const string &getHost() const {
        return host;
    }

    const string &getRealName() const {
        return realName;
    }

    void setRealName(const string &realName) {
        Client::realName = realName;
    }

    bool isOpMode() const {
        return opMode;
    }

    void setOpMode(bool opMode) {
        Client::opMode = opMode;
    }

    void pushMessage(RawMessage *outMessage);

    const char *getHostName();

    void sendMessages();

    ChannelHandler *getChannelHandler() const;

    UserHandler *getUserHandler() const;
};


#endif //FT_IRC_CLIENT_H
