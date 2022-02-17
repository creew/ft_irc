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
    int startPos = 0, endPos;
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

void Part::partChannel(Client *client, const string &channel, const string &umsg) {
    Channel * ch = client->getChannelHandler()->findChannelByName(channel);
    if (ch == NULL) {
        CommonReplies::sendNoSuchChannel(client, channel);
    } else {
        Client *cl = client->getUserHandler()->findClientByFd(client->getFd());
        if (cl == NULL) {
            CommonReplies::sendNotOnChannel(client, channel);
        } else {
            client->getChannelHandler()->removeClientFromChannel(client);
            RawMessage *msg = new ClientRawMessage(client, "PART %s :%s", channel.c_str(), umsg.c_str());
            CommonReplies::sendAllChannelUsers(client, channel, msg);
        }
    }
}

const char *Part::getName() {
    return "PART";
}

