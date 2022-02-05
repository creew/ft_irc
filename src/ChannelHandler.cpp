#include <unistd.h>
#include "ChannelHandler.h"
#include "messages/ClientRawMessage.h"

bool ChannelHandler::joinChannel(Client *client, const string &name) {
    Channel *channel = findChannelByName(name);
    if (channel != NULL) {
        return channel->putUser(client);
    }
    channel = new Channel(name);
    channels.push_back(channel);
    channel->addToOps(client);
    return channel->putUser(client);
}

void ChannelHandler::disconnectUserFromServer(Client *client) {
    close(client->getFd());
    removeClientFromChannel(client);
}

void ChannelHandler::removeClientFromChannel(Client *client) {
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

bool ChannelHandler::sendMessageToChannel(Client *clientFrom, string &channelTo, string &message) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = *ic;
        if ((channel->isNoMessagesOutside() && !channel->isUserOnChannel(clientFrom)) ||
            (channel->isModeratedChannel() &&
             (!channel->isUserOps(clientFrom) && !channel->isUserVoiced(clientFrom)))) {
            RawMessage *msg = new RawMessage(":%s %03d %s %s :Cannot send to channel", clientFrom->getHostName(),
                                             ERR_CANNOTSENDTOCHAN, clientFrom->getNick().c_str(), channelTo.c_str());
            clientFrom->pushMessage(msg);
            return false;

        }
        if (channel->getName() == channelTo) {
            vector<Client *> users = channel->getUsers();
            for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
                Client *client = (*iu);
                if (client != clientFrom) {
                    RawMessage *msg = new ClientRawMessage(clientFrom, "PRIVMSG %s :%s", channelTo.c_str(), message.c_str());
                    client->pushMessage(msg);
                }
            }
            return true;
        }
    }
    RawMessage *msg = new RawMessage(":%s %03d %s %s :No such channel", clientFrom->getHostName(), ERR_NOSUCHCHANNEL,
                                     clientFrom->getNick().c_str(), channelTo.c_str());
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
