#include <sys/socket.h>
#include <arpa/inet.h>
#include "Server.h"
#include <sys/poll.h>
#include <iostream>
#include <netdb.h>
#include <sys/fcntl.h>
#include "RawMessage.h"

void Server::start() {
    startListen();
}

Server::Server(ServerConfiguration *configuration) : configuration(configuration) {
    this->client_socket = 0;
    this->commandProcessor = new CommandProcessor();
}

Server::~Server() {
    cout << "hello from destructor" << endl;
    delete commandProcessor;
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

int Server::initNetworkServer() {
    struct sockaddr_in server_sockaddr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw std::invalid_argument("can't open socket");
    }
    setSocketOptions(sock);
    server_sockaddr.sin_family = AF_INET;
    Server::getRemoteAddr(&server_sockaddr, configuration->getHost());
    server_sockaddr.sin_port = htons(configuration->getPortNetwork());
    if (bind(sock, (struct sockaddr *) &server_sockaddr,
             sizeof(server_sockaddr)) < 0) {
        throw invalid_argument("ERROR on binding");
    }
    return sock;
}

void Server::startListen() {
    int totalFd;
    //initNetworkServer();
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
                setSocketOptions(new_sd);
                cout << "  New incoming connection - " << new_sd << std::endl;
                IClient *client = new Client(new_sd, this);
                clients.push_back(client);
            } while (new_sd != -1);
        }
        for (int i = 1; i < totalFd; i++) {
            if (polls[i].revents & POLLIN) {
                for (vector<IClient *>::iterator client = clients.begin(); client != clients.end(); client++) {
                    char buf[1025];
                    if ((*client)->getFd() == polls[i].fd) {
                        int r = recv(polls[i].fd, buf, sizeof(buf) - 1, 0);
                        buf[r] = '\0';
                        if (r == 0) {
                            cout << "  Disconnecting - " << polls[i].fd << endl;
                            delete (*client);
                            clients.erase(client--);
                        } else {
                            cout << buf;
                            (*client)->processData(buf, r);
                        }
                    }
                }
            } else if (polls[i].revents & POLLOUT) {
                for (vector<IClient *>::iterator client = clients.begin(); client != clients.end(); client++) {
                    if ((*client)->getFd() == polls[i].fd) {
                        vector<RawMessage *> *msgs = (*client)->getSendQueue();
                        if (!msgs->empty()) {
                            RawMessage *msg = msgs->at(0);
                            long r = send(polls[i].fd, msg->getMessage(), msg->getLength(), 0);
                            if (r > 0) {
                                if (r == msg->getLength()) {
                                    delete msg;
                                    msgs->erase(msgs->begin());
                                } else {
                                    msg->reduceLength(r);
                                }
                            }
                        }
                    }
                }
            }
        }
    }  while (run);
}

void Server::getRemoteAddr(struct sockaddr_in *sockaddrIn, const string& addr) {
    struct hostent *host = gethostbyname(addr.c_str());
    if (host == nullptr) {
        throw invalid_argument("can't get host by addr");
    }
    memmove(&(sockaddrIn->sin_addr.s_addr), host->h_addr_list[0], 4);
}

int Server::fillPoll(struct pollfd *polls, int maxSize) {
    int i = 0;
    polls[i].fd = client_socket;
    polls[i++].events = POLLIN | POLLOUT;
    for (vector<IClient *>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (i < maxSize) {
            polls[i].fd = (*it)->getFd();
            polls[i++].events = POLLIN | POLLOUT;
        } else {
            cerr << "Maximum number of clients reached";
            break;
        }
    }
    return i;
}

const vector<IClient *> &Server::getClients() const {
    return clients;
}

const vector<Channel *> &Server::getChannels() const {
    return channels;
}
