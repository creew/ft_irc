//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_SERVER_H
#define FT_IRC_SERVER_H

#include <netinet/in.h>
#include "ServerConfiguration.h"
class Server
{
private:
    int client_socket;
    struct sockaddr_in client_sockaddr;
    int server_socket;
    struct sockaddr_in server_sockaddr;
    bool run;

    Configuration configuration;

    void initRecvSocket();
    bool initSendSocket();
    void startListen();
    static void getRemoteAddr(sockaddr_in *sockaddrIn, const std::string &addr);
public:
    virtual ~Server();

    Server(const Configuration &configuration);
    void start();

};


#endif //FT_IRC_SERVER_H
