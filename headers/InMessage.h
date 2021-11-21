#ifndef FT_IRC_INMESSAGE_H
#define FT_IRC_INMESSAGE_H


#include <vector>

class InMessage {
private:
    char *prefix;
    char *command;
    std::vector<char *> params;
public:
    InMessage() : prefix(nullptr), command(nullptr) { }

    explicit InMessage(const char *message);

    virtual ~InMessage();

    char *getPrefix() const;

    char *getCommand() const;

    const std::vector<char *> &getParams() const;
};

#endif //FT_IRC_INMESSAGE_H
