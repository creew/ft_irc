#ifndef FT_IRC_NICK_H
#define FT_IRC_NICK_H

#include "ICommand.h"

class Nick : public ICommand{
    bool run(IClient *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_NICK_H
