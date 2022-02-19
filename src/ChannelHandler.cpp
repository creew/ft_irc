#include <unistd.h>
#include "ChannelHandler.h"
#include "messages/ClientRawMessage.h"

Channel *ChannelHandler::joinChannel(Client *client, const string &name) {
    Channel *channel = findChannelByName(name);
    if (channel != NULL) {
        return channel->putUser(client) ? channel : NULL;
    }
    channel = new Channel(name);
    channels.push_back(channel);
    channel->modifyOps(client, true);
    return channel->putUser(client) ? channel : NULL;
}

void ChannelHandler::disconnectUserFromServer(Client *client) {
    close(client->getFd());
    removeClientFromAllChannels(client);
}

void ChannelHandler::removeClientFromAllChannels(Client *client) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = (*ic);
        channel->removeUser(client);
        if (channel->usersCount() == 0) {
            delete channel;
            channels.erase(ic--);
        }
    }
}

void ChannelHandler::removeClientFromChannel(Channel *channel, Client *client) {
    vector<Channel *>::iterator id = find(channels.begin(), channels.end(), channel);
    if (id != channels.end()) {
        channel->removeUser(client);
        if (channel->usersCount() == 0) {
            delete channel;
            channels.erase(id);
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

bool ChannelHandler::sendMessageToChannel(Client *clientFrom, const string &type, const string &channelTo, const string &message) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = *ic;
        if ((channel->isModeActive('n') && !channel->isUserOnChannel(clientFrom)) ||
            ((channel->isModeActive('m') &&
             (!channel->isUserOps(clientFrom) && !channel->isUserVoiced(clientFrom))))) {
            RawMessage *msg = new RawMessage(clientFrom->getHostName(), ERR_CANNOTSENDTOCHAN, clientFrom->getNick().c_str(),
                                             "%s :Cannot send to channel", channelTo.c_str());
            clientFrom->pushMessage(msg);
            return false;
        }
        if (channel->getName() == channelTo) {
            vector<Client *> users = channel->getUsers();
            for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
                Client *client = (*iu);
                if (client != clientFrom) {
                    RawMessage *msg = new ClientRawMessage(clientFrom, "%s %s :%s", type.c_str(), channelTo.c_str(), message.c_str());
                    client->pushMessage(msg);
                }
            }
            return true;
        }
    }
    RawMessage *msg = new RawMessage(clientFrom->getHostName(), ERR_NOSUCHCHANNEL,
                                     clientFrom->getNick().c_str(), "%s :No such channel", channelTo.c_str());
    clientFrom->pushMessage(msg);
    return false;
}

Channel *ChannelHandler::findChannelByName(const string &channel) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *ch = *ic;
        if (ch->getName() == channel) {
            return ch;
        }
    }
    return NULL;
}
