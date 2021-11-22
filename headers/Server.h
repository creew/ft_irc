#ifndef FT_IRC_SERVER_H
#define FT_IRC_SERVER_H

#include <netinet/in.h>
#include <vector>
#include "ServerConfiguration.h"
#include "Channel.h"
#include "CommandProcessor.h"
#include "ChannelHandler.h"

using namespace std;

class ChannelHandler;
class Client;
class Server
{
private:
    int client_socket;

    vector<Client *> clients;
    bool run;

    ServerConfiguration *configuration;
    CommandProcessor *commandProcessor;
    ChannelHandler *channelHandler;

    int fillPoll(struct pollfd *polls, int maxSize);
    void initRecvSocket();
    int initNetworkServer();
    void startListen();
    void setSocketOptions(int socket);
    static void getRemoteAddr(sockaddr_in *sockaddrIn, const std::string &addr);
public:
    virtual ~Server();

    vector<Client *> &getClients();

    vector<Channel *> &getChannels();

    const ServerConfiguration *getConfiguration() const;

    CommandProcessor *getCommandProcessor() const;

    explicit Server(ServerConfiguration *configuration);

    void start();
};


#endif //FT_IRC_SERVER_H
