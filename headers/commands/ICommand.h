#ifndef FT_IRC_ICOMMAND_H
#define FT_IRC_ICOMMAND_H

#include "messages/InMessage.h"
#include <Client.h>

class Client;
class ICommand {
public:
    virtual bool run(Client *client, InMessage *message) = 0;

    virtual const char *getName() = 0;

    virtual ~ICommand() {};

    static bool isChannel(const string &s) {
        if (s.length() > 0) {
            char c = s.at(0);
            return  (c == '&' || c == '#' || c == '!' || c == '+');
        }
        return false;
    }
};


#endif //FT_IRC_ICOMMAND_H
