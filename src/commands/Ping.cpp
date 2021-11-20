#include <RawMessage.h>

#include "commands/Ping.h"

void Ping::run(IClient *client, InMessage *message) {
    RawMessage *msg = new RawMessage(":%s PONG %s :%s", client->getHostName(), client->getHostName(), client->getNick());
    client->pushMessage(msg);
}

const char *Ping::getName() {
    return "PING";
}
