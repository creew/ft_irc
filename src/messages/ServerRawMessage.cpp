#include "messages/ServerRawMessage.h"

ServerRawMessage::ServerRawMessage(const char *format, ...) : RawMessage() {
    int bodyLength;
    char *buf;
    va_list args, copy_args;
    va_start(args, format);
    __va_copy(copy_args, args);
    bodyLength = vsnprintf(NULL, 0, format, args);
    buf = new char[bodyLength + 1];
    vsnprintf(buf, bodyLength + 1, format, copy_args);
    va_end(args);
    add(buf, bodyLength);
}

void ServerRawMessage::add(char *buf, int length) {
    this->length += length;
    messages.push(new MessageInner(buf, length));
}

void ServerRawMessage::copy(const char *buf) {
    int length = strlen(buf);
    char *n = new char[length + 1];
    strcpy(n, buf);
    add(n, length);
}

ServerRawMessage::~ServerRawMessage() {
    while (!messages.empty())
    {
        delete messages.front();
        messages.pop();
    }
}

void ServerRawMessage::finalize() {
    int pos = 0;
    addConst("\r\n");
    delete this->message;
    this->message = new char[this->length + 1];
    while (!messages.empty())
    {
        MessageInner *inner = messages.front();
        memcpy(this->message + pos, inner->buf, inner->size);
        pos += inner->size;
        delete inner;
        messages.pop();
    }
    this->length = pos;
    this->message[pos] = '\0';
}

void ServerRawMessage::addConst(const char *buf) {
    int l = strlen(buf);
    this->length += l;
    messages.push(new MessageInner(const_cast<char *>(buf), l, true));
}
