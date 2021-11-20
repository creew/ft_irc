#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Client.h"
#include "StringUtils.h"

Client::Client(int fd, IServer *server) :
        fd(fd),
        server(server),
        user(nullptr),
        nick(nullptr),
        recvBufLength(0) {
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

void Client::processData(const char *data, int length) {
    if (length + recvBufLength > sizeof(this->recvBuf)) {
        std::cerr << "unsupported length message received, clean";
        this->recvBufLength = 0;
        this->state = BODY;
        if (length > sizeof(this->recvBuf)) {
            std::cerr << "unsupported length message received, exit";
            return;
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
                    processCommand(this->recvBuf);
                    this->recvBufLength = 0;
                }
                this->state = BODY;
        }
    }
}

void Client::processCommand(char *buf) {
    server->getCommandProcessor()->processAction(buf, this);
}

const char *Client::getServerPassword() {
    const ServerConfiguration *configuration = this->server->getConfiguration();
    if (configuration) {
        return configuration->getPassword().c_str();
    }
    return nullptr;
}

void Client::setUser(char *const user) {
    this->user = StringUtils::duplicateString(user);
}

void Client::setNick(char *const nick) {
    this->nick = StringUtils::duplicateString(nick);
}

void Client::pushMessage(RawMessage *outMessage) {
    sendQueue.push_back(outMessage);
}

const char *Client::getHostName() {
    return "localhost";
}
