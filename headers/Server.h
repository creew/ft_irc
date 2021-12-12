#ifndef FT_IRC_SERVER_H
#define FT_IRC_SERVER_H

#include <netinet/in.h>
#include <vector>
#include "ServerConfiguration.h"
#include "Channel.h"
#include "CommandProcessor.h"
#include "ChannelHandler.h"
#include "UserHandler.h"

using namespace std;

class ChannelHandler;
class UserHandler;
class Client;
class Server
{
private:
    int client_socket;
    bool run;

    ServerConfiguration *configuration;
    CommandProcessor *commandProcessor;
    ChannelHandler *channelHandler;
    UserHandler *userHandler;

    int fillPoll(struct pollfd *polls, int maxSize);
    void initRecvSocket();
    void startListen();
    static void setSocketOptions(int socket);
    void acceptNewConnection(const pollfd *polls);
public:
    virtual ~Server();

    explicit Server(ServerConfiguration *configuration);

    void start();

    ServerConfiguration *getConfiguration() const {
        return configuration;
    }

    CommandProcessor *getCommandProcessor() const {
        return commandProcessor;
    }

    ChannelHandler *getChannelHandler() const {
        return channelHandler;
    }

    UserHandler *getUserHandler() const {
        return userHandler;
    }
};


#endif //FT_IRC_SERVER_H
