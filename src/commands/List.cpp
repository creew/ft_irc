#include <Errors.h>
#include <RawMessage.h>
#include "commands/List.h"

bool List::run(IClient *client, InMessage *message) {
    sendRplListStart(client);
    return false;
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
    std::vector<Channel *> channels = client->getChannels();
    for (std::vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        RawMessage *msg = new RawMessage(":%s %03d %s %s %d  Name", client->getHostName(), RPL_LIST, (*ic)->getName().c_str(),
                                         client->getNick());
        client->pushMessage(msg);
    }
    sendRplEnd(client);
}

void List::sendRplEnd(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :End of /LIST", client->getHostName(), RPL_LISTEND, client->getNick());
    client->pushMessage(msg);
}
