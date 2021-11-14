//
// Created by Edythe Klompus on 11/13/21.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include "Server.h"
#include <sys/poll.h>
#include <iostream>
#include <netdb.h>
#include <sys/fcntl.h>
#include "Client.h"

void Server::start() {

    startListen();
}

Server::Server(const Configuration *configuration) : configuration(configuration) {
    this->client_socket = 0;
    memset(&this->client_sockaddr, 0, sizeof(this->client_sockaddr));
    this->server_socket = 0;
    memset(&this->server_sockaddr, 0, sizeof(this->server_sockaddr));
    this->configuration = configuration;
}

void Server::initRecvSocket() {
    int yes = 1;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1){
        throw std::invalid_argument("can't open socket");
    }
    int flags = fcntl(client_socket, F_GETFL, 0);
    flags |= O_NONBLOCK;
    if (fcntl(client_socket, F_SETFL, flags) < 0) {
        throw std::invalid_argument("can't set nonblock");
    }
    if (setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        throw std::invalid_argument("can't setsockopt");
    }
    client_sockaddr.sin_family = AF_INET;
    client_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_sockaddr.sin_port = htons(configuration->port);
    if (bind(client_socket, (struct sockaddr *) &client_sockaddr,
             sizeof(client_sockaddr)) < 0) {
        throw std::invalid_argument("ERROR on binding");
    }
    if (listen(client_socket, 10) == -1) {
        throw std::invalid_argument("ERROR on listen");
    }
}



bool Server::initSendSocket() {
    if (!configuration->host.empty() && !configuration->password_network.empty()) {
        int yes = 1;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1){
            throw std::invalid_argument("can't open socket");
        }
        if (fcntl(server_socket, F_SETFL, O_NONBLOCK) < 0) {
            throw std::invalid_argument("can't set nonblock");
        }
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            throw std::invalid_argument("can't setsockopt");
        }
        server_sockaddr.sin_family = AF_INET;
        Server::getRemoteAddr(&server_sockaddr, configuration->host);
        server_sockaddr.sin_port = htons(configuration->port_network);
        if (bind(server_socket, (struct sockaddr *) &client_sockaddr,
                 sizeof(server_sockaddr)) < 0) {
            throw std::invalid_argument("ERROR on binding");
        }
        return true;
    }
    return false;
}

void Server::startListen() {
    int totalFd;
    initRecvSocket();
    bool serverSocket = initSendSocket();
    struct pollfd polls[100];
    run = true;
    do {
        totalFd = fillPoll(polls, sizeof(polls) / sizeof(polls[0]), serverSocket);
        int ret = poll(polls, totalFd, -1);
        if (ret < 0) {
            throw std::invalid_argument(std::string ("ERROR on poll") + strerror(errno));
        }
        if (ret == 0) {
            throw std::invalid_argument("timeout excepted");
        }
        if (polls[0].revents) {
            int new_sd;
            do
            {
                new_sd = accept(polls[0].fd, nullptr, nullptr);
                if (new_sd < 0) {
                    if (errno != EWOULDBLOCK) {
                        run = false;
                    }
                    break;
                }
                if (fcntl(new_sd, F_SETFL, O_NONBLOCK) < 0) {
                    throw std::invalid_argument("can't set nonblock");
                }
                printf("  New incoming connection - %d\n", new_sd);
                Client *client = new Client(new_sd, configuration);
                clients.push_back(client);
            } while (new_sd != -1);
        }
        if (serverSocket) {

        }
        for (int i = server_socket ? 2 : 1; i < totalFd; i++) {
            char buf[1024];
            if (polls[i].revents) {
                for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it) {
                    if ((*it)->getFd() == polls[i].fd) {
                        int r = recv(polls[i].fd, buf, sizeof(buf), 0);
                        if (r == 0) {
                            delete (*it);
                            clients.erase(it--);
                        } else {
                            std::cout << buf << std::endl;
                            (*it)->processData(buf, r);
                        }
                    }
                }
            }
        }
    }  while (run);
}



Server::~Server() {
    std::cout << "hello from destructor" << std::endl;
}

void Server::getRemoteAddr(struct sockaddr_in *sockaddrIn, const std::string& addr) {
    struct hostent *host = gethostbyname(addr.c_str());
    if (host == nullptr) {
        throw std::invalid_argument("can't get host by addr");
    }
    memmove(&(sockaddrIn->sin_addr.s_addr), host->h_addr_list[0], 4);
}

int Server::fillPoll(struct pollfd *polls, int maxSize, bool serverSocket) {
    int i = 0;
    polls[i].fd = client_socket;
    polls[i++].events = POLLIN;
    if (serverSocket) {
        polls[i].fd = server_socket;
        polls[i++].events = POLLOUT;
    }
    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (i < maxSize) {
            polls[i].fd = (*it)->getFd();
            polls[i++].events = POLLIN;
        }
        else {
            std::cerr << "Maximum number of clients reached";
            break;
        }
    }
    return i;
}
