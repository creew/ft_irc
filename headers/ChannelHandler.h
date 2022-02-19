#ifndef FT_IRC_CHANNELHANDLER_H
#define FT_IRC_CHANNELHANDLER_H

#include <string>
#include "Client.h"
#include "Errors.h"

using namespace std;

class ChannelHandler {
private:
    vector<Channel *> channels;
public:
    virtual ~ChannelHandler();

    const vector<Channel *> &getChannels() const;

    Channel *joinChannel(Client *client, const string &name);
    void removeClientFromAllChannels(Client *client);
    void removeClientFromChannel(Channel *channel, Client *client);
    bool sendMessageToChannel(Client *clientFrom, const string &type, const string &channelTo, const string &message);
    Channel *findChannelByName(const string &channel);

    void disconnectUserFromServer(Client *client);
};


#endif //FT_IRC_CHANNELHANDLER_H
