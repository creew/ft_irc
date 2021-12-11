#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#include "StringUtils.h"

Client::Client(int fd, Server *server, char *ip) :
        fd(fd),
        server(server),
        user(nullptr),
        nick(nullptr), recvBuf(),
        recvBufLength(0), state(), ip(ip) {
}

Client::~Client() {
    close(this->fd);
    delete(this->user);
    delete(this->nick);
    for (std::vector<RawMessage *>::iterator it = sendQueue.begin(); it != sendQueue.end(); it++) {
        delete (*it);
        sendQueue.erase(it--);
    }
}

bool Client::processData(const char *data, size_t length) {
    if (length + recvBufLength > sizeof(this->recvBuf)) {
        std::cerr << "unsupported length message received, clean";
        this->recvBufLength = 0;
        this->state = BODY;
        if (length > sizeof(this->recvBuf)) {
            std::cerr << "unsupported length message received, exit";
            return false;
        }
    }

    for (int i = 0; i < length; i++) {
        switch (this->state) {
            case BODY:
                this->recvBuf[this->recvBufLength++] = data[i];
                if (data[i] == '\r')
                    state = CR;
                break;
            case CR:
                this->recvBuf[this->recvBufLength++] = data[i];
                if (data[i] != '\n') {
                    std::cout << "cr received, lf not, continue body";
                }
                else {
                    this->recvBuf[this->recvBufLength - 2] = '\0';
                    if (processCommand(this->recvBuf)) {
                        return true;
                    }
                    this->recvBufLength = 0;
                }
                this->state = BODY;
        }
    }
    return false;
}

bool Client::processCommand(char *buf) {
    return server->getCommandProcessor()->processAction(buf, this);
}

const char *Client::getServerPassword() {
    const ServerConfiguration *configuration = this->server->getConfiguration();
    if (configuration) {
        return configuration->getPassword().c_str();
    }
    return nullptr;
}

void Client::setUser(const char *user) {
    this->user = StringUtils::duplicateString(user);
}

void Client::setNick(const char *nick) {
    this->nick = StringUtils::duplicateString(nick);
}

void Client::pushMessage(RawMessage *outMessage) {
    sendQueue.push_back(outMessage);
}

const char *Client::getHostName() {
    return "localhost";
}

void Client::sendMessages() {
    if (!sendQueue.empty()) {
        RawMessage *msg = sendQueue.at(0);
        long r = send(this->getFd(), msg->getMessage(), msg->getLength(), 0);
        if (r > 0) {
            if (r == msg->getLength()) {
                delete msg;
                sendQueue.erase(sendQueue.begin());
            } else {
                msg->reduceLength(r);
            }
        }
    }
}

int Client::getFd() const {
    return fd;
}

char *Client::getUser() const {
    return user;
}

char *Client::getNick() const {
    return nick;
}

ChannelHandler *Client::getChannelHandler() const {
    return server->getChannelHandler();
}

UserHandler *Client::getUserHandler() const {
    return server->getUserHandler();
}
