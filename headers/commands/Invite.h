//
// Created by Edythe Klompus on 2/19/22.
//

#ifndef FT_IRC_INVITE_H
#define FT_IRC_INVITE_H


#include "Client.h"

class Invite : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
};


#endif //FT_IRC_INVITE_H
