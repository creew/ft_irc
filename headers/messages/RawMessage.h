#ifndef FT_IRC_RAWMESSAGE_H
#define FT_IRC_RAWMESSAGE_H

#include <cstddef>

class RawMessage {
protected:
    char *message;
    int length;
public:
    RawMessage(const char *format, ...);

    RawMessage(const char *hostName, int msgId, const char *target, const char *format, ...);

    RawMessage();

    virtual ~RawMessage();

    char *getMessage() const {
        return message;
    }

    int getLength() const {
        return length;
    }

    void reduceLength(long reduce);

    RawMessage *clone();
};


#endif //FT_IRC_RAWMESSAGE_H
