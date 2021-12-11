#include "commands/Topic.h"
#include "commands/CommonReplies.h"

bool Topic::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    string channelName = message->getParams().at(0);
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL || !channel->isUserOnChannel(client)) {
        CommonReplies::sendNotOnChannel(client, channelName.c_str());
        return false;
    }
    if (message->getParams().size() > 1) {
        if (!channel->isTopicSettable()) {
            CommonReplies::sendNotChannelOperator(client, channelName.c_str());
        } else {
            string topic = message->getParams().at(1);
            RawMessage *msg = new RawMessage(":%s!%s@%s TOPIC %s :%s", client->getNick(), client->getUser(),
                                             client->getIp().c_str(), channelName.c_str(), topic.c_str());
            client->pushMessage(msg);
        }
    } else {
        if (channel->getTopic().empty()) {
            sendNoTopic(client, channelName.c_str());
        } else {
            sendTopic(client, channelName.c_str(), channel->getTopic().c_str());
        }
    }
    return false;
}

void Topic::sendNoTopic(Client *client, const char *channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No topic is set", client->getHostName(), RPL_NOTOPIC, channel);
    client->pushMessage(msg);
}

void Topic::sendTopic(Client *client, const char *channel, const char *topic) {
    RawMessage *msg = new RawMessage(":%s %03d %s :%s", client->getHostName(), RPL_TOPIC, channel, topic);
    client->pushMessage(msg);
}

const char *Topic::getName() {
    return "TOPIC";
}
