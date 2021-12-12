#ifndef FT_IRC_NAMES_H
#define FT_IRC_NAMES_H


#include "ICommand.h"
#include "messages/ServerRawMessage.h"

class Names : public ICommand{
public:
    bool run(Client *client, InMessage *message);

    const char *getName();

    static void addUser(ServerRawMessage *msg, Channel *channel, Client *client);

    static void sendChannelUsers(Client *client, const string &channelName);
};

#endif //FT_IRC_NAMES_H
