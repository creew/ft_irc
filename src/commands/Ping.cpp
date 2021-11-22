#include <RawMessage.h>

#include "commands/Ping.h"

bool Ping::run(Client *client, InMessage *message) {
    RawMessage *msg = new RawMessage(":%s PONG %s :%s", client->getHostName(), client->getHostName(), client->getNick());
    client->pushMessage(msg);
    return false;
}

const char *Ping::getName() {
    return "PING";
}
