//
// Created by Edythe Klompus on 11/14/21.
//

#include "Message.h"
#include "StringUtils.h"

Message::Message(const char *message) {
    const char *d;
    message = StringUtils::skipSpaces(message);
    if (*message == ':') {
        message++;
        d = StringUtils::skipNonSpaces(message);
        if (d == message) {
            return;
        }
        this->prefix = StringUtils::duplicateString(message, d - message);
        message = StringUtils::skipSpaces(d);
    }
    d = StringUtils::skipNonSpaces(message);
    if (*d == '\0') {
        return;
    }
    this->command = StringUtils::duplicateString(message, d - message);
    message = StringUtils::skipSpaces(d);
    StringUtils::splitMessage(&this->params, message);
}

Message::~Message() {
    delete this->prefix;
    delete this->command;
    for (std::vector<char *>::iterator it = params.begin(); it != params.end(); ++it) {
        delete (*it);
        params.erase(it--);
    }
}

char *Message::getPrefix() const {
    return prefix;
}

char *Message::getCommand() const {
    return command;
}

const std::vector<char *> &Message::getParams() const {
    return params;
}
