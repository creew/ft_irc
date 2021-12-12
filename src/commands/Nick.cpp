#include "commands/Nick.h"
#include "commands/CommonReplies.h"

bool Nick::run(Client *client, InMessage *message) {
    if (!message->getParams().empty()) {
        client->setNick(message->getParams().at(0));
    }
    CommonReplies::sendRplWelcome(client);
    return false;
}

const char *Nick::getName() {
    return "NICK";
}

