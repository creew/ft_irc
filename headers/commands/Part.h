#ifndef FT_IRC_PART_H
#define FT_IRC_PART_H

#include "ICommand.h"

class Part : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();

    static void partChannel(Client *client, const string &channel, const string &msg) ;
};


#endif //FT_IRC_PART_H
