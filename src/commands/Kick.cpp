#include "commands/Kick.h"
#include "commands/CommonReplies.h"
#include "messages/ClientRawMessage.h"

bool Kick::run(Client *client, InMessage *message) {
    if (message->getParams().size() < 2) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    string channelName = message->getParams().at(0);
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL) {
        CommonReplies::sendNoSuchChannel(client, channelName);
        return false;
    }
    if (!channel->isUserOnChannel(client)) {
        CommonReplies::sendNotOnChannel(client, channelName);
        return false;
    }
    if (!channel->isUserOps(client)) {
        CommonReplies::sendNotChannelOperator(client, channelName);
        return false;
    }
    string nickName = message->getParams().at(1);
    Client *kickClient = client->getUserHandler()->findClientByNick(nickName);
    if (kickClient == NULL || !channel->isUserOnChannel(kickClient)) {
        CommonReplies::sendNoSuchNickOrChannel(client, nickName);
        return false;
    }
    string s = message->getParams().size() > 2 ? message->getParams().at(2) : "";
    RawMessage *rawMessage = new ClientRawMessage(client, "KICK %s %s %s", channel->getName().c_str(),
                                                  nickName.c_str(), s.c_str());
    CommonReplies::sendAllChannelUsers(client, channel, rawMessage);
    client->getChannelHandler()->removeClientFromChannel(channel, kickClient);
    return false;
}

const char *Kick::getName() {
    return "KICK";
}
