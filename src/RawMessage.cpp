#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "RawMessage.h"

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

RawMessage::RawMessage(size_t length, const char *buf) : length(length) {
    this->message = new char[length];
    memcpy(this->message, buf, length);
}

RawMessage::~RawMessage() {
    delete this->message;
}

void RawMessage::reduceLength(long reduce) {
    strcpy(this->message, this->message + reduce);
    this->length = this->length - reduce;
}

