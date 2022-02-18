#include <cstddef>
#include "messages/ClientRawMessage.h"

ClientRawMessage::ClientRawMessage(Client *client, const char *format...) : RawMessage() {
    int prefixLength, bodyLength;
    va_list args, copy_args;
    va_start(args, format);
    __va_copy(copy_args, args);
    prefixLength = snprintf(NULL, 0, CLIENT_MSG_PREFIX,
                            client->getNick().c_str(), client->getUser().c_str(), client->getHost().c_str());
    bodyLength = vsnprintf(NULL, 0, format, args);
    this->message = new char[bodyLength + prefixLength + 3];
    snprintf(this->message, prefixLength + 1, CLIENT_MSG_PREFIX,
             client->getNick().c_str(), client->getUser().c_str(), client->getHost().c_str());
    vsnprintf(this->message + prefixLength, bodyLength + 1, format, copy_args);
    strcpy(this->message + prefixLength + bodyLength, "\r\n");
    this->length = prefixLength + bodyLength + 2;
    va_end(args);
}