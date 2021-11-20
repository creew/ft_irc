#ifndef FT_IRC_SERVER_H
#define FT_IRC_SERVER_H

#include <netinet/in.h>
#include <vector>
#include "ServerConfiguration.h"
#include "Client.h"
#include "IServer.h"
#include "Channel.h"
#include "CommandProcessor.h"

using namespace std;

class Server : public IServer
{
private:
    int client_socket;

    vector<IClient *> clients;
    vector<Channel *> channels;
    bool run;

    ServerConfiguration *configuration;
    CommandProcessor *commandProcessor;

    int fillPoll(struct pollfd *polls, int maxSize);
    void initRecvSocket();
    int initNetworkServer();
    void startListen();
    void setSocketOptions(int socket);
    static void getRemoteAddr(sockaddr_in *sockaddrIn, const std::string &addr);
public:
    virtual ~Server();

    const vector<IClient *> &getClients() const;

    const vector<Channel *> &getChannels() const;

    virtual const ServerConfiguration *getConfiguration() const {
        return configuration;
    }

    CommandProcessor *getCommandProcessor() const {
        return commandProcessor;
    }

    explicit Server(ServerConfiguration *configuration);
    void start();

};


#endif //FT_IRC_SERVER_H
