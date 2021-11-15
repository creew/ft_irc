//
// Created by Edythe Klompus on 11/14/21.
//

#ifndef FT_IRC_MESSAGE_H
#define FT_IRC_MESSAGE_H


#include <vector>

class Message {
private:
    char *prefix;
    char *command;
    std::vector<char *> params;
public:
    Message() : prefix(nullptr), command(nullptr) { }

    Message(const char *message);

    Message(char *prefix, char *command, const std::vector<char *> &params);

    virtual ~Message();

    char *getPrefix() const;

    char *getCommand() const;

    const std::vector<char *> &getParams() const;

    void parseMessage(const char *message);
};

#endif //FT_IRC_MESSAGE_H
