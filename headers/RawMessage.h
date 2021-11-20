#ifndef FT_IRC_RAWMESSAGE_H
#define FT_IRC_RAWMESSAGE_H

#include <cstddef>
class RawMessage {
private:
    char *message;
    int length;
public:
    RawMessage(const char *format, ...);

    RawMessage(size_t length, const char *buf);

    virtual ~RawMessage();

    char *getMessage() const {
        return message;
    }

    int getLength() const {
        return length;
    }

    void reduceLength(long reduce);
};


#endif //FT_IRC_RAWMESSAGE_H
