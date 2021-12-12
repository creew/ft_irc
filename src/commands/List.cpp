#include <Errors.h>
#include "messages/RawMessage.h"
#include "commands/List.h"

bool List::run(Client *client, InMessage *message) {
    sendRplListStart(client);
    return false;
}

const char *List::getName() {
    return "LIST";
}

void List::sendRplListStart(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s Channel :Users  Name", client->getHostName(), RPL_LISTSTART, client->getNick().c_str());
    client->pushMessage(msg);
    sendRplList(client);
}

void List::sendRplList(Client *client) {
    vector<Channel *> channels = client->getChannelHandler()->getChannels();
    for (std::vector<Channel *>::iterator ic = channels.begin(); ic != channels.end(); ic++) {
        RawMessage *msg = new RawMessage(":%s %03d %s %s %d :%s", client->getHostName(), RPL_LIST, client->getNick().c_str(),
                                         (*ic)->getName().c_str(), (*ic)->usersCount(), (*ic)->getTopic().c_str());
        client->pushMessage(msg);
    }
    sendRplEnd(client);
}

void List::sendRplEnd(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :End of /LIST", client->getHostName(), RPL_LISTEND, client->getNick().c_str());
    client->pushMessage(msg);
}
