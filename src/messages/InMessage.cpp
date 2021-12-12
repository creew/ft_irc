#include "messages/InMessage.h"
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
        this->prefix = std::string(message, d - message);
        message = StringUtils::skipSpaces(d);
    }
    d = StringUtils::skipNonSpaces(message);
    this->command = std::string(message, d - message);
    message = StringUtils::skipSpaces(d);
    StringUtils::splitMessage(this->params, message);
}
