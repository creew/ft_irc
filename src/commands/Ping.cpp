#include "messages/RawMessage.h"

#include "commands/Ping.h"

bool Ping::run(Client *client, InMessage *message) {
    (void) message;
    RawMessage *msg = new RawMessage(":%s PONG %s :%s", client->getHostName(), client->getHostName(),
                                     client->getNick().c_str());
    client->pushMessage(msg);
    return false;
}

const char *Ping::getName() {
    return "PING";
}
