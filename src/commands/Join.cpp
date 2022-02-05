#include <commands/CommonReplies.h>
#include <iostream>
#include "commands/Join.h"
#include "ChannelHandler.h"
#include "messages/ClientRawMessage.h"
#include "commands/Names.h"
#include "commands/Nick.h"

bool Join::run(Client *client, InMessage *message) {
    if (message->getParams().empty()) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
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
        RawMessage *msg = new ClientRawMessage(client, "JOIN :%s", channel.c_str());
        CommonReplies::sendAllChannelUsers(client, channel, msg);
        Names::sendChannelUsers(client, channel);
    }
}

const char *Join::getName() {
    return "JOIN";
}
