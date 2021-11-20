#include <Errors.h>
#include "CommonReplies.h"

void CommonReplies::sendRplWelcome(IClient *client) {
    if (client->getNick() && client->getUser()) {
        RawMessage *msg = new RawMessage(":%s %03d %s :Welcome to the localhost IRC Network %s!%s@localhost",
                                         client->getHostName(), RPL_WELCOME, client->getNick(), client->getNick(), client->getUser());
        client->pushMessage(msg);
        sendRplYourHost(client);
    }
}

void CommonReplies::sendRplYourHost(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :Your host is %s, running version 1.000.00",
                                     client->getHostName(), RPL_YOURHOST, client->getNick(), "localhost");
    client->pushMessage(msg);
    sendRplCreated(client);
}

void CommonReplies::sendRplCreated(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :This server was created 11.11.2021",
                                     client->getHostName(), RPL_CREATED, client->getNick());
    client->pushMessage(msg);
    sendRplMyInfo(client);
}

void CommonReplies::sendRplMyInfo(IClient *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :%s",
                                     client->getHostName(), RPL_MYINFO, client->getHostName(), client->getNick());
    client->pushMessage(msg);
}
