#ifndef FT_IRC_SERVERRAWMESSAGE_H
#define FT_IRC_SERVERRAWMESSAGE_H

#include <queue>
#include "RawMessage.h"

class ServerRawMessage : public RawMessage {
private:
    struct MessageInner {
    public:
        char *buf;
        int size;
        bool perm;
    public:
        MessageInner(char *buf, int size, bool perm = false) :
                buf(buf), size(size), perm(perm) {}

        virtual ~MessageInner() {
            if (!perm) {
                delete (buf);
            }
        }
    };
    std::queue<MessageInner *> messages;
public:
    ServerRawMessage(const char *format, ...);

    virtual ~ServerRawMessage();

    void copy(const char *buf);

    void add(char *buf, int length);

    void addConst(const char *buf);

    void finalize();
};

#endif //FT_IRC_SERVERRAWMESSAGE_H
