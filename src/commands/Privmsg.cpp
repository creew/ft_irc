#include <commands/CommonReplies.h>
#include "commands/Privmsg.h"

bool Privmsg::run(Client *client, InMessage *message) {
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
        client->getChannelHandler()->sendMessageToChannel(client, to, msg);
    } else {
        client->getUserHandler()->sendMessageToUser(client, to, msg);
    }
    return false;
}

const char *Privmsg::getName() {
    return "PRIVMSG";
}
