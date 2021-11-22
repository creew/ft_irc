//
// Created by Алексей on 23.11.2021.
//

#include <commands/CommonReplies.h>
#include "commands/Privmsg.h"

bool Privmsg::run(Client *client, InMessage *message) {
    if (message->getParams().empty()) {
        CommonReplies::sendNoRecipientGiven(client, message->getCommand());
        return false;
    }
    if (message->getParams().size() < 2) {
        CommonReplies::sendNoTextToSend(client);
        return false;
    }

    return false;
}

const char *Privmsg::getName() {
    return "PRIVMSG";
}
