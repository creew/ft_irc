#ifndef FT_IRC_KICK_H
#define FT_IRC_KICK_H

#include "Client.h"

class Kick : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
};


#endif //FT_IRC_KICK_H
