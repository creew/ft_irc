#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#include "StringUtils.h"

Client::Client(int fd, Server *server, char *host) :
        fd(fd), server(server), opMode(false), recvBuf(),
        recvBufLength(0), state(), host(host), registered(false) {
}

Client::~Client() {
    close(this->fd);
    while (!sendQueue.empty()) {
        delete(sendQueue.front());
        sendQueue.pop();
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
                break;
        }
    }
    return false;
}

bool Client::processCommand(char *buf) {
    return server->getCommandProcessor()->processAction(buf, this);
}

const string &Client::getServerPassword() {
    return server->getConfiguration()->getPassword();
}

void Client::pushMessage(RawMessage *outMessage) {
    sendQueue.push(outMessage);
}

const char *Client::getHostName() {
    return "localhost";
}

void Client::sendMessages() {
    if (!sendQueue.empty()) {
        RawMessage *msg = sendQueue.front();
        long r = send(this->getFd(), msg->getMessage(), msg->getLength(), 0);
        if (r > 0) {
            if (r == msg->getLength()) {
                delete msg;
                sendQueue.pop();
            } else {
                msg->reduceLength(r);
            }
        }
    }
}

int Client::getFd() const {
    return fd;
}

ChannelHandler *Client::getChannelHandler() const {
    return server->getChannelHandler();
}

UserHandler *Client::getUserHandler() const {
    return server->getUserHandler();
}

bool Client::operator==(const Client &rhs) const {
    return nick == rhs.nick;
}

bool Client::operator!=(const Client &rhs) const {
    return !(rhs == *this);
}
