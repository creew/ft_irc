//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_SERVER_H
#define FT_IRC_SERVER_H

#include <netinet/in.h>
#include <vector>
#include "ServerConfiguration.h"
#include "Client.h"

class Server
{
private:
    int client_socket;
    struct sockaddr_in client_sockaddr;
    int server_socket;
    struct sockaddr_in server_sockaddr;
    std::vector<Client *> clients;
    bool run;

    const Configuration *configuration;

    int fillPoll(struct pollfd *polls, int maxSize, bool serverSocket);
    void initRecvSocket();
    bool initSendSocket();
    void startListen();
    void setSocketOptions(int socket);
    static void getRemoteAddr(sockaddr_in *sockaddrIn, const std::string &addr);
public:
    virtual ~Server();

    explicit Server(const Configuration *configuration);
    void start();


};


#endif //FT_IRC_SERVER_H
