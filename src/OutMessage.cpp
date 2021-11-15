//
// Created by Алексей on 15.11.2021.
//

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "OutMessage.h"

OutMessage::OutMessage(const char *format...) {
    va_list args;
    va_start(args, format);
    this->length = vsnprintf(NULL, 0, format, args);
    this->message = new char[this->length + 3];
    vsnprintf(this->message, this->length + 1, format, args);
    strcpy(this->message + this->length, "\r\n");
    this->length += 2;
    va_end(args);
}

OutMessage::~OutMessage() {
    delete this->message;
}

void OutMessage::reduceLength(long reduce) {
    strcpy(this->message, this->message + reduce);
    this->length = this->length - reduce;
}
