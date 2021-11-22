#ifndef FT_IRC_PING_H
#define FT_IRC_PING_H


#include "ICommand.h"

class Ping : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
};


#endif //FT_IRC_PING_H
