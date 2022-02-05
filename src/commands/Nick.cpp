#include "commands/Nick.h"
#include "commands/CommonReplies.h"

bool Nick::run(Client *client, InMessage *message) {
    if (message->getParams().empty()) {
        CommonReplies::sendNoNickNameGiven(client);
        return false;
    }
    string nick = message->getParams().at(0);
    if (client->getUserHandler()->findClientByNick(nick) != NULL) {
        CommonReplies::sendNickNameInUse(client, nick);
        return false;
    }
    if (!client->isRegistered()) {
        client->setNick(nick);
        CommonReplies::sendRplWelcome(client);
        client->setRegistered(true);
    } else {
        //:eklomp|2!kvirc@195.133.239.83 NICK :asd
        ServerRawMessage *msg = new ServerRawMessage(":%s!%s@%s %s :%s", client->getNick().c_str(), client->getUser().c_str(), client->getHost().c_str(), getName(),
                                                     message->getParams().at(0).c_str());
        msg->finalize();
        sendOnSameChannelsUsers(client, msg);
        client->setNick(nick);
    }
    return false;
}

const char *Nick::getName() {
    return "NICK";
}

void Nick::mergeChannelUsers(vector<Client *> &allChUsers, vector<Client *> &merge) {
    for (vector<Client *>::iterator ic = merge.begin(); ic != merge.end(); ic++) {
        Client *forMerge = *ic;
        bool add = true;
        for (vector<Client *>::iterator icc = merge.begin(); ic != merge.end(); icc++) {
            Client *chUser = *icc;
            if (*chUser == *forMerge) {
                add = false;
                break;
            }
        }
        if (add) {
            allChUsers.push_back(forMerge);
        }
    }
}

void Nick::sendOnSameChannelsUsers(Client *client, RawMessage *message) {
    vector<Channel *> channels = client->getChannelHandler()->getChannels();
    vector<Client *> allChUsers;
    for (vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        Channel *channel = *ic;
        vector<Client *> users = channel->getUsers();
        vector<Client *> channelUsers;
        bool isChUser = false;
        for (vector<Client *>::iterator icc = users.begin(); icc != users.end(); icc++) {
            Client *chClient = *icc;
            if (*chClient == *client) {
                isChUser = true;
            } else {
                channelUsers.push_back(chClient);
            }
        }
        if (isChUser) {
            mergeChannelUsers(allChUsers, channelUsers);
        }
    }
    allChUsers.push_back(client);
    for (vector<Client *>::iterator ic = allChUsers.begin(); ic != allChUsers.end(); ic++) {
        Client *cl = *ic;
        cl->pushMessage(message->clone());
    }
    delete message;
}
