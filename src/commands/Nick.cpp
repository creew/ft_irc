#include "commands/Nick.h"
#include "CommonReplies.h"

void Nick::run(IClient *client, InMessage *message) {
    if (!message->getParams().empty()) {
        client->setNick(message->getParams().at(0));
    }
    CommonReplies::sendRplWelcome(client);
}

const char *Nick::getName() {
    return "NICK";
}

