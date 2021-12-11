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
    channel->addToOps(client);
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

bool ChannelHandler::sendMessageToChannel(Client *clientFrom, string &channelTo, string &message) {
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = *ic;
        if ((channel->isNoMessagesOutside() && !channel->isUserOnChannel(clientFrom)) ||
            (channel->isModeratedChannel() &&
             (!channel->isUserOps(clientFrom) && !channel->isUserVoiced(clientFrom)))) {
            RawMessage *msg = new RawMessage(":%s %03d %s %s :Cannot send to channel", clientFrom->getHostName(),
                                             ERR_CANNOTSENDTOCHAN, clientFrom->getNick(), channelTo.c_str());
            clientFrom->pushMessage(msg);
            return false;

        }
        if (channel->getName() == channelTo) {
            vector<Client *> users = channel->getUsers();
            for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
                Client *client = (*iu);
                if (client != clientFrom) {
                    RawMessage *msg = new RawMessage(":%s!%s@%s PRIVMSG %s :%s", clientFrom->getNick(),
                                                     clientFrom->getUser(), clientFrom->getIp().c_str(), channelTo.c_str(), message.c_str());
                    client->pushMessage(msg);
                }
            }
            return true;
        }
    }
    RawMessage *msg = new RawMessage(":%s %03d %s %s :No such channel", clientFrom->getHostName(), ERR_NOSUCHCHANNEL,
                                     clientFrom->getNick(), channelTo.c_str());
    clientFrom->pushMessage(msg);
    return false;
}
