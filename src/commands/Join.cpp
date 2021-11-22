//
// Created by Алексей on 21.11.2021.
//

#include <commands/CommonReplies.h>
#include "commands/Join.h"
#include "ChannelHandler.h"

bool Join::run(Client *client, InMessage *message) {
    if (message->getParams().size() < 1) {
        CommonReplies::sendNotEnoughParameters(client, message->getCommand());
        return false;
    }
    client->getChannelHandler()->joinChannel(client, message->getParams().at(0));
    return false;
}

const char *Join::getName() {
    return "JOIN";
}
