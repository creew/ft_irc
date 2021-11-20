#ifndef FT_IRC_PASS_H
#define FT_IRC_PASS_H

#include "ICommand.h"

class Pass : public ICommand{
    void run(IClient *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_PASS_H
