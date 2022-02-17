#include "commands/Notice.h"
#include "commands/CommonReplies.h"

bool Notice::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNoRecipientGiven(client, message->getCommand());
        return false;
    }
    if (message->getParams().size() < 2 || message->getParams().at(1).empty()) {
        CommonReplies::sendNoTextToSend(client);
        return false;
    }
    string to = message->getParams().at(0);
    string msg = message->getParams().at(1);
    if (isChannel(to)) {
        client->getChannelHandler()->sendMessageToChannel(client, message->getCommand(), to, msg);
    } else {
        client->getUserHandler()->sendMessageToUser(client, message->getCommand(), to, msg);
    }
    return false;
}

const char *Notice::getName() {
    return "NOTICE";
}
