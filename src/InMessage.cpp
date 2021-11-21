#include "InMessage.h"
#include "StringUtils.h"

InMessage::InMessage(const char *message) {
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
    this->command = StringUtils::duplicateString(message, d - message);
    message = StringUtils::skipSpaces(d);
    StringUtils::splitMessage(this->params, message);
}

InMessage::~InMessage() {
    delete this->prefix;
    delete this->command;
    for (std::vector<char *>::iterator it = params.begin(); it != params.end(); it++) {
        delete (*it);
        params.erase(it--);
    }
}

char *InMessage::getPrefix() const {
    return prefix;
}

char *InMessage::getCommand() const {
    return command;
}

const std::vector<char *> &InMessage::getParams() const {
    return params;
}
