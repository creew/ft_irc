//
// Created by Алексей on 21.11.2021.
//

#ifndef FT_IRC_JOIN_H
#define FT_IRC_JOIN_H

#include "ICommand.h"

class Join : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
private:

};

#endif //FT_IRC_JOIN_H
