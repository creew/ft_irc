#include <iostream>
#include "commands/Part.h"
#include "commands/CommonReplies.h"
#include "messages/ClientRawMessage.h"

bool Part::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    string msg;
    if (message->getParams().size() > 1) {
        msg = message->getParams().at(1);
    }
    std::basic_string<char>::size_type startPos = 0;
    std::basic_string<char>::size_type endPos;
    string channel;
    string param = message->getParams().at(0);
    while ((endPos = param.find(',', startPos)) != std::string::npos) {
        channel = param.substr(startPos, endPos - startPos);
        std::cout << channel << std::endl;
        partChannel(client, channel, msg);
        startPos = endPos + 1;
    }
    channel = param.substr(startPos);
    partChannel(client, channel, msg);
    return false;
}

void Part::partChannel(Client *client, const string &channelName, const string &umsg) {
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL) {
        CommonReplies::sendNoSuchChannel(client, channelName);
    } else {
        if (!channel->isUserOnChannel(client)) {
            CommonReplies::sendNotOnChannel(client, channelName);
        } else {
            RawMessage *msg = new ClientRawMessage(client, "PART %s :%s", channelName.c_str(), umsg.c_str());
            CommonReplies::sendAllChannelUsers(client, channel, msg);
            client->getChannelHandler()->removeClientFromChannel(channel, client);
        }
    }
}

const char *Part::getName() {
    return "PART";
}

