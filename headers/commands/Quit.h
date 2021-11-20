#ifndef FT_IRC_QUIT_H
#define FT_IRC_QUIT_H

#include "ICommand.h"

class Quit : public ICommand{
    void run(IClient *client, InMessage *message);

    const char *getName();
};

#endif //FT_IRC_QUIT_H
