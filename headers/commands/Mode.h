#ifndef FT_IRC_MODE_H
#define FT_IRC_MODE_H


#include "commands/ICommand.h"

class Mode : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
};


#endif //FT_IRC_MODE_H
