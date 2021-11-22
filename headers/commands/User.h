#ifndef FT_IRC_USER_H
#define FT_IRC_USER_H

#include "ICommand.h"

class User : public ICommand {
    bool run(Client *client, InMessage *message);

    const char *getName();

private:
    void sendErrNeedMoreParams(Client *client, const char *command);
};

#endif //FT_IRC_USER_H
