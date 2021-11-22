#include <unistd.h>
#include "ChannelHandler.h"

bool ChannelHandler::joinChannel(Client *client, const string &name) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = (*ic);
        if (channel->getName() == name) {
            return channel->putUser(client);
        }
    }
    Channel *channel = new Channel(name);
    channels.push_back(channel);
    return channel->putUser(client);
}

void ChannelHandler::removeClientFromChannel(Client *client) {
    close(client->getFd());
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = (*ic);
        channel->removeUser(client);
        if (channel->usersCount() == 0) {
            delete channel;
            channels.erase(ic--);
        }
    }
}

const vector<Channel *> &ChannelHandler::getChannels() const {
    return channels;
}

ChannelHandler::~ChannelHandler() {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        delete *ic;
        channels.erase(ic--);
    }
}
