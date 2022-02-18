#include <sys/socket.h>
#include <arpa/inet.h>
#include "Server.h"
#include <sys/poll.h>
#include <iostream>
#include <netdb.h>
#include <sys/fcntl.h>
#include <Client.h>
#include <cerrno>
#include "messages/RawMessage.h"
#include "UserHandler.h"

extern char stopAll;
void Server::start() {
    startListen();
}

Server::Server(ServerConfiguration *configuration) :
        client_socket(0),
        run(false),
        configuration(configuration) {
    this->commandProcessor = new CommandProcessor();
    this->channelHandler = new ChannelHandler();
    this->userHandler = new UserHandler();
    this->channelModeHandler = new ChannelModeHandler();
}

Server::~Server() {
    delete commandProcessor;
    delete channelHandler;
    delete userHandler;
    delete channelModeHandler;
}

void Server::initRecvSocket() {
    struct sockaddr_in client_sockaddr;
    memset(&client_sockaddr, 0, sizeof(client_sockaddr));
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1){
        throw std::invalid_argument("can't open socket");
    }
    setSocketOptions(client_socket);
    client_sockaddr.sin_family = AF_INET;
    client_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_sockaddr.sin_port = htons(configuration->getPort());
    if (bind(client_socket, (struct sockaddr *) &client_sockaddr,
             sizeof(client_sockaddr)) < 0) {
        throw invalid_argument("ERROR on binding");
    }
    if (listen(client_socket, 10) == -1) {
        throw invalid_argument("ERROR on listen");
    }
}

void Server::setSocketOptions(int socket) {
    int yes = 1;
    int flags = fcntl(socket, F_GETFL, 0);
    flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) < 0) {
        throw invalid_argument("can't set nonblock");
    }
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        throw invalid_argument("can't setsockopt");
    }
}

void Server::startListen() {
    int totalFd;
    initRecvSocket();
    struct pollfd polls[100];
    run = true;
    do {
        totalFd = fillPoll(polls, sizeof(polls) / sizeof(polls[0]));
        int ret = poll(polls, totalFd, -1);
        if (ret < 0) {
            throw invalid_argument(std::string ("ERROR on poll") + strerror(errno));
        }
        if (ret == 0) {
            throw invalid_argument("timeout excepted");
        }
        if (polls[0].revents) {
            acceptNewConnection(polls);
        }
        for (int i = 1; i < totalFd; i++) {
            if (polls[i].revents & POLLIN) {
                Client *client = userHandler->findClientByFd(polls[i].fd);
                if (client != NULL) {
                    char buf[1025];
                    size_t r = recv(polls[i].fd, buf, sizeof(buf) - 1, 0);
                    buf[r] = '\0';
                    cout << buf;
                    if (r == 0 || client->processData(buf, r)) {
                        cout << "  Disconnecting - " << polls[i].fd << endl;
                        channelHandler->disconnectUserFromServer(client);
                        userHandler->removeClient(polls[i].fd);
                    }
                }
            } else if (polls[i].revents & POLLOUT) {
                userHandler->sendMessages(polls[i].fd);
            }
        }
    }  while (run);
}

void Server::acceptNewConnection(const pollfd *polls) {
    int fd;
    struct hostent *hp;
    struct sockaddr_in sockaddrIn;
    do
    {
        socklen_t socklen = sizeof (sockaddrIn);
        fd = accept(polls[0].fd, (struct sockaddr *) &sockaddrIn, &socklen);
        if (fd < 0) {
            if (errno != EWOULDBLOCK) {
                run = false;
            }
            break;
        }
        setSocketOptions(fd);
        cout << "  New incoming connection - " << fd << endl;
        char *ip;
        if ((hp = gethostbyaddr(&sockaddrIn, socklen, AF_INET)) == NULL) {
            ip = inet_ntoa(sockaddrIn.sin_addr);
        } else {
            ip = hp->h_name;
        }
        Client *client = new Client(fd, this, ip);
        userHandler->joinUser(client);
    } while (fd != -1);
}

int Server::fillPoll(struct pollfd *polls, int maxSize) {
    int i = 0;
    polls[i].fd = client_socket;
    polls[i++].events = POLLIN | POLLOUT;
    i += userHandler->fillPoll(polls + i, maxSize - i, POLLIN | POLLOUT);
    return i;
}
