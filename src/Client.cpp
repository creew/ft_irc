//
// Created by Алексей on 14.11.2021.
//

#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#include "CommandProcessor.h"
#include "StringUtils.h"
#include "Errors.h"

Client::Client(int fd, const Configuration *serverConfiguration) :
fd(fd), serverConfiguration(serverConfiguration), user(nullptr), recvBufLength(0), sendBufLength(0) {
}

Client::~Client() {
    close(this->fd);
    delete(this->user);
    delete(this->nick);
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
                    std::cout << "not crlf received, continue body";
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
    sendBufLength = snprintf(this->sendBuf, sizeof(this->sendBuf), "%03d %s %s :Not enough parameters\r\n", ERR_NEEDMOREPARAMS, this->nick, command);
    send(this->fd, this->sendBuf, this->sendBufLength, 0);
}

void Client::sendRplWelcome() {
    if (this->nick && this->user) {
        sendBufLength = snprintf(this->sendBuf, sizeof(this->sendBuf),
                                 ":hello %03d %s :Welcome to the localhost IRC Network %s!%s@localhost\r\n",
                                 RPL_WELCOME, this->nick, this->nick, this->user);
        send(this->fd, this->sendBuf, this->sendBufLength, 0);
        sendRplYourHost();
    }
}

void Client::sendRplYourHost() {
    sendBufLength = snprintf(this->sendBuf, sizeof(this->sendBuf),
                             ":hello %03d %s :Your host is %s, running version 1.000.00\r\n",
                             RPL_YOURHOST, this->nick, "localhost");
    send(this->fd, this->sendBuf, this->sendBufLength, 0);
    sendRplCreated();
}

void Client::sendRplCreated() {
    sendBufLength = snprintf(this->sendBuf, sizeof(this->sendBuf),
                             ":hello %03d %s :This server was created 11.11.2021\r\n",
                             RPL_CREATED, this->nick);
    send(this->fd, this->sendBuf, this->sendBufLength, 0);
    sendRplMyInfo();
}

void Client::sendRplMyInfo() {
    sendBufLength = snprintf(this->sendBuf, sizeof(this->sendBuf),
                             ":hello %03d %s :localhost 1.000.00 1123 1123\r\n",
                             RPL_MYINFO, this->nick);
    send(this->fd, this->sendBuf, this->sendBufLength, 0);
}