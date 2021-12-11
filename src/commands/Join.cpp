#include <commands/CommonReplies.h>
#include <iostream>
#include "commands/Join.h"
#include "ChannelHandler.h"

bool Join::run(Client *client, InMessage *message) {
    if (message->getParams().empty()) {
        CommonReplies::sendNotEnoughParameters(client, message->getCommand());
        return false;
    }
    string param = message->getParams().at(0);
    int startPos = 0, endPos;
    string channel;
    while ((endPos = param.find(',', startPos)) != std::string::npos) {
        channel = param.substr(startPos, endPos - startPos);
        std::cout << channel << std::endl;
        joinChannel(client, channel);
        startPos = endPos + 1;
    }
    channel = param.substr(startPos);
    joinChannel(client, channel);
    return false;
}

void Join::joinChannel(Client *client, const string &channel) const {
    if (client->getChannelHandler()->joinChannel(client, channel)) {
        RawMessage *msg = new RawMessage(":%s!%s@%s JOIN :%s", client->getNick(), client->getUser(),
                                         client->getIp().c_str(), channel.c_str());
        client->pushMessage(msg);
    }
}

const char *Join::getName() {
    return "JOIN";
}
