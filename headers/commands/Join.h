#ifndef FT_IRC_JOIN_H
#define FT_IRC_JOIN_H

#include "ICommand.h"

class Join : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
private:
    void joinChannel(Client *client, const string &channelName) const;
};

#endif //FT_IRC_JOIN_H
