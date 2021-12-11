#ifndef FT_IRC_PRIVMSG_H
#define FT_IRC_PRIVMSG_H


#include "ICommand.h"

class Privmsg : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
};


#endif //FT_IRC_PRIVMSG_H
