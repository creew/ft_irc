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

    bool joinChannel(Client *client, const string &name);
    void removeClientFromChannel(Client *client);
    bool sendMessageToChannel(Client *clientFrom, string &channel, string &message);
};


#endif //FT_IRC_CHANNELHANDLER_H
