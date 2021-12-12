#ifndef FT_IRC_INMESSAGE_H
#define FT_IRC_INMESSAGE_H


#include <vector>
#include <string>

class InMessage {
private:
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
public:
    InMessage(const char *message);

    const std::string &getPrefix() const {
        return prefix;
    }

    const std::string &getCommand() const {
        return command;
    }

    const std::vector<std::string> &getParams() const {
        return params;
    }
};

#endif //FT_IRC_INMESSAGE_H
