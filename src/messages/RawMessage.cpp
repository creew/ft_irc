#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "messages/RawMessage.h"
#include "Client.h"

RawMessage::RawMessage(const char *format...) {
    va_list args, copy_args;
    va_start(args, format);
    va_copy(copy_args, args);
    this->length = vsnprintf(NULL, 0, format, args);
    this->message = new char[this->length + 3];
    vsnprintf(this->message, this->length + 1, format, copy_args);
    strcpy(this->message + this->length, "\r\n");
    this->length += 2;
    va_end(args);
}

RawMessage::RawMessage() : message(nullptr), length(0) {}

RawMessage::~RawMessage() {
    delete this->message;
}

void RawMessage::reduceLength(long reduce) {
    strcpy(this->message, this->message + reduce);
    this->length = this->length - reduce;
}

RawMessage *RawMessage::clone() {
    RawMessage *clone = new RawMessage();
    clone->message = new char[this->length + 1];
    strcpy(clone->message, this->message);
    clone->length = this->length;
    return clone;
}

RawMessage::RawMessage(const char *hostName, int msgId, const char *target, const char *format, ...) {
    int firstPartLength, secondPartLength;
    va_list args, copy_args;
    va_start(args, format);
    va_copy(copy_args, args);
    firstPartLength = snprintf(NULL, 0, ":%s %03d %s ", hostName, msgId, target);
    secondPartLength = vsnprintf(NULL, 0, format, args);
    this->length = firstPartLength + secondPartLength;
    this->message = new char[this->length + 3];
    snprintf(this->message, firstPartLength + 1, ":%s %03d %s ", hostName, msgId, target);
    vsnprintf(this->message + firstPartLength, secondPartLength + 1, format, copy_args);
    strcpy(this->message + this->length, "\r\n");
    this->length += 2;
    va_end(args);
}

