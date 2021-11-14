//
// Created by Алексей on 14.11.2021.
//

#include <cstring>
#include <unistd.h>
#include <iostream>
#include "Client.h"
#include "CommandProcessor.h"

Client::Client(int fd, const Configuration *serverConfiguration) : fd(fd), serverConfiguration(serverConfiguration) {
    this->fd = fd;
    this->username = NULL;
    this->bufLength = 0;
    this->serverConfiguration = serverConfiguration;
}

Client::~Client() {
    close(this->fd);
    delete(this->username);
}

void Client::processData(const char *data, int length) {
    if (length + bufLength > sizeof(this->buf)) {
        std::cerr << "unsupported length message received, clean";
        this->bufLength = 0;
        this->state = BODY;
    }
    if (length > sizeof(this->buf)) {
        std::cerr << "unsupported length message received, exit";
        return;
    }
    for (int i = 0; i < length; i++) {
        switch (this->state) {
            case BODY:
                this->buf[this->bufLength++] = data[i];
                if (data[i] == '\r')
                    state = CR;
                break;
            case CR:
                this->buf[this->bufLength++] = data[i];
                if (data[i] != '\n') {
                    std::cout << "not crlf received, continue body";
                }
                else {
                    this->buf[this->bufLength - 2] = '\0';
                    processCommand(this->buf);
                    this->bufLength = 0;
                }
                this->state = BODY;
        }
    }
}

void Client::processCommand(char *buf) {
    CommandProcessor::processAction(buf, this->serverConfiguration);
}

int Client::getFd() const {
    return fd;
}
