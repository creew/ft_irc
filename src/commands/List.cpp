#include <Errors.h>
#include <RawMessage.h>
#include "commands/List.h"

void List::run(IClient *client, InMessage *message) {
    sendRplListStart(client);
}

const char *List::getName() {
    return "LIST";
}

void List::sendRplListStart(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s Channel :Users  Name", client->getHostName(), RPL_LISTSTART, client->getNick());
    client->pushMessage(msg);
    sendRplList(client);
}

void List::sendRplList(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s Channel :Users  Name", client->getHostName(), RPL_LIST, client->getNick());
    client->pushMessage(msg);
    sendRplEnd(client);
}

void List::sendRplEnd(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :End of /LIST", client->getHostName(), RPL_LISTEND, client->getNick());
    client->pushMessage(msg);
}