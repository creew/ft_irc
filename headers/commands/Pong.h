#ifndef FT_IRC_PONG_H
#define FT_IRC_PONG_H

#include "ICommand.h"

class Pong : public ICommand{
    bool run(IClient *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_PONG_H
