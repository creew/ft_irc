#ifndef FT_IRC_INMESSAGE_H
#define FT_IRC_INMESSAGE_H


#include <vector>
#include <string>

class InMessage {
private:
    char *prefix;
    char *command;
    std::vector<std::string> params;
public:
    InMessage() : prefix(nullptr), command(nullptr) { }

    explicit InMessage(const char *message);

    virtual ~InMessage();

    char *getPrefix() const;

    char *getCommand() const;

    std::vector<std::string> &getParams();
};

#endif //FT_IRC_INMESSAGE_H
