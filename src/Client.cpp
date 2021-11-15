//
// Created by Алексей on 14.11.2021.
//

#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Client.h"
#include "CommandProcessor.h"
#include "StringUtils.h"
#include "Errors.h"

Client::Client(int fd, const Configuration *serverConfiguration) :
        fd(fd),
        serverConfiguration(serverConfiguration),
        user(nullptr),
        nick(nullptr),
        recvBufLength(0) {
}

Client::~Client() {
    close(this->fd);
    delete(this->user);
    delete(this->nick);
    for (std::vector<OutMessage *>::iterator it = sendQueue.begin(); it != sendQueue.end(); it++) {
        delete (*it);
        sendQueue.erase(it--);
    }
}

void Client::processData(const char *data, int length) {
    if (length + recvBufLength > sizeof(this->recvBuf)) {
        std::cerr << "unsupported length message received, clean";
        this->recvBufLength = 0;
        this->state = BODY;
    }
    if (length > sizeof(this->recvBuf)) {
        std::cerr << "unsupported length message received, exit";
        return;
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
    CommandProcessor::processAction(buf, this);
}

int Client::getFd() const {
    return fd;
}

const char *Client::getServerPassword() {
    if (this->serverConfiguration) {
        return this->serverConfiguration->password.c_str();
    }
    return nullptr;
}

void Client::setUser(char *const user) {
    this->user = StringUtils::duplicateString(user);
}

void Client::setNick(char *const nick) {
    this->nick = StringUtils::duplicateString(nick);
}

void Client::sendErrNeedMoreParams(const char *command) {
    OutMessage *msg = new OutMessage("%03d %s %s :Not enough parameters", ERR_NEEDMOREPARAMS, this->nick, command);
    sendQueue.push_back(msg);
}

void Client::sendRplWelcome() {
    if (this->nick && this->user) {
        OutMessage *msg = new OutMessage(":hello %03d %s :Welcome to the localhost IRC Network %s!%s@localhost",
                                         RPL_WELCOME, this->nick, this->nick, this->user);
        sendQueue.push_back(msg);
        sendRplYourHost();
    }
}

void Client::sendRplYourHost() {
    OutMessage *msg = new OutMessage(":hello %03d %s :Your host is %s, running version 1.000.00",
                                     RPL_YOURHOST, this->nick, "localhost");
    sendQueue.push_back(msg);
    sendRplCreated();
}

void Client::sendRplCreated() {
    OutMessage *msg = new OutMessage(":hello %03d %s :This server was created 11.11.2021",
                               RPL_CREATED, this->nick);
    sendQueue.push_back(msg);
    sendRplMyInfo();
}

void Client::sendRplMyInfo() {
    OutMessage *msg = new OutMessage(":hello %03d %s :localhost 1.000.00 1123 1123",
                                     RPL_MYINFO, this->nick);
    sendQueue.push_back(msg);
}

void Client::sendPong() {
    OutMessage *msg = new OutMessage("PONG %s", this->nick);
    sendQueue.push_back(msg);
}
