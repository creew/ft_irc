#ifndef FT_IRC_CHANNELHANDLER_H
#define FT_IRC_CHANNELHANDLER_H

#include <string>
#include "Client.h"

using namespace std;

class ChannelHandler {
private:
    vector<Channel *> channels;
    bool putUserToChannel(Client *client, const Channel *channel);
public:
    virtual ~ChannelHandler();

    const vector<Channel *> &getChannels() const;

    bool joinChannel(Client *client, const string &name);
    void removeClientFromChannel(Client *client);
};


#endif //FT_IRC_CHANNELHANDLER_H
