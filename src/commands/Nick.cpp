#include "commands/Nick.h"
#include "CommonReplies.h"

bool Nick::run(IClient *client, InMessage *message) {
    if (!message->getParams().empty()) {
        client->setNick(message->getParams().at(0));
    }
    CommonReplies::sendRplWelcome(client);
    return false;
}

const char *Nick::getName() {
    return "NICK";
}

