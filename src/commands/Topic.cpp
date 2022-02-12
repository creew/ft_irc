#include "commands/Topic.h"
#include "commands/CommonReplies.h"
#include "messages/ClientRawMessage.h"

bool Topic::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    string channelName = message->getParams().at(0);
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL || !channel->isUserOnChannel(client)) {
        CommonReplies::sendNotOnChannel(client, channelName);
        return false;
    }
    if (message->getParams().size() > 1) {
        if (channel->isModeActive("t") && !channel->isUserOps(client)) {
            CommonReplies::sendNotChannelOperator(client, channelName);
        } else {
            string topic = message->getParams().at(1);
            RawMessage *msg = new ClientRawMessage(client, "TOPIC %s :%s", channelName.c_str(), topic.c_str());
            CommonReplies::sendAllChannelUsers(client, channelName, msg);
            channel->setTopic(topic);
        }
    } else {
        if (channel->getTopic().empty()) {
            sendNoTopic(client, channelName);
        } else {
            sendTopic(client, channelName, channel->getTopic().c_str());
        }
    }
    return false;
}

void Topic::sendNoTopic(Client *client, const string &channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No topic is set", client->getHostName(), RPL_NOTOPIC, channel.c_str());
    client->pushMessage(msg);
}

void Topic::sendTopic(Client *client, const string &channel, const char *topic) {
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_TOPIC, client->getNick().c_str(),
                                     "%s :%s", channel.c_str(), topic);
    client->pushMessage(msg);
}

const char *Topic::getName() {
    return "TOPIC";
}
