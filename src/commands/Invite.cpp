#include "commands/Invite.h"
#include "commands/CommonReplies.h"
#include "messages/ServerRawMessage.h"
#include "messages/ClientRawMessage.h"

const char *Invite::getName() {
    return "INVITE";
}

bool Invite::run(Client *client, InMessage *message) {
    if (message->getParams().size() < 2) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    string nickName = message->getParams().at(0);
    Client *invited = client->getUserHandler()->findClientByNick(nickName);
    if (invited == NULL) {
        CommonReplies::sendNoSuchNickOrChannel(client, nickName);
        return false;
    }
    string channelName = message->getParams().at(1);
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL || !channel->isUserOnChannel(client)) {
        CommonReplies::sendNotOnChannel(client, channelName);
        return false;
    }
    if (!channel->isUserOps(client)) {
        CommonReplies::sendNotChannelOperator(client, channelName);
        return false;
    }
    if (channel->isUserOnChannel(invited)) {
        CommonReplies::sendUserOnChannel(client, nickName, channelName);
        return false;
    }
    RawMessage *rawMessage = new ClientRawMessage(client, "INVITE %s :%s", nickName.c_str(), channelName.c_str());
    invited->pushMessage(rawMessage);
    channel->modifyInvited(invited, true);
    return false;
}
