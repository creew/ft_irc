#ifndef FT_IRC_NICK_H
#define FT_IRC_NICK_H

#include "ICommand.h"
#include "messages/ServerRawMessage.h"

class Nick : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();

public:
    static void sendOnSameChannelsUsers(Client *client, RawMessage *message);
private:
    static void mergeChannelUsers(vector<Client *> &allChUsers, vector<Client *> &merge);
};

#endif //FT_IRC_NICK_H
