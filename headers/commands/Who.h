#ifndef FT_IRC_WHO_H
#define FT_IRC_WHO_H


#include "ICommand.h"

class Who : public ICommand {
    bool run(Client *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_WHO_H
