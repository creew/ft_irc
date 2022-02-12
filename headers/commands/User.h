#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "ICommand.h"

class User : public ICommand {
    bool run(Client *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_USER_H
