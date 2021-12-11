#include <Errors.h>
#include "commands/CommonReplies.h"

void CommonReplies::sendRplWelcome(Client *client) {
    if (client->getNick() && client->getUser()) {
        RawMessage *msg = new RawMessage(":%s %03d %s :Welcome to the localhost IRC Network %s!%s@localhost",
                                         client->getHostName(), RPL_WELCOME, client->getNick(), client->getNick(), client->getUser());
        client->pushMessage(msg);
        sendRplYourHost(client);
    }
}

void CommonReplies::sendRplYourHost(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :Your host is %s, running version 1.000.00",
                                     client->getHostName(), RPL_YOURHOST, client->getNick(), "localhost");
    client->pushMessage(msg);
    sendRplCreated(client);
}

void CommonReplies::sendRplCreated(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :This server was created 11.11.2021",
                                     client->getHostName(), RPL_CREATED, client->getNick());
    client->pushMessage(msg);
    sendRplMyInfo(client);
}

void CommonReplies::sendRplMyInfo(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :%s",
                                     client->getHostName(), RPL_MYINFO, client->getHostName(), client->getNick());
    client->pushMessage(msg);
}

void CommonReplies::sendNeedMoreParams(Client *client, const char *command) {
    RawMessage *msg = new RawMessage(":%s %03d %s :Not enough parameters",
                                     client->getHostName(), ERR_NEEDMOREPARAMS, command);
    client->pushMessage(msg);
}

void CommonReplies::sendNoTextToSend(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No text to send",
                                     client->getHostName(), ERR_NOTEXTTOSEND, client->getNick());
    client->pushMessage(msg);
}

void CommonReplies::sendNoRecipientGiven(Client *client, const char *command) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No recipient given (%s)",
                                     client->getHostName(), ERR_NORECIPIENT, client->getNick(), command);
    client->pushMessage(msg);
}

void CommonReplies::sendNoSuchChannel(Client *client, const char *channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No such channel",
                                     client->getHostName(), ERR_NOSUCHCHANNEL, channel);
    client->pushMessage(msg);
}

void CommonReplies::sendNotOnChannel(Client *client, const char *channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :You're not on that channel",
                                     client->getHostName(), ERR_NOTONCHANNEL, channel);
    client->pushMessage(msg);
}

void CommonReplies::sendNotChannelOperator(Client *client, const char *channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :You're not channel operator",
                                     client->getHostName(), ERR_NOTONCHANNEL, channel);
    client->pushMessage(msg);
}

void CommonReplies::sendNoSuchServer(Client *client, const char *channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No such server",
                                     client->getHostName(), ERR_NOSUCHSERVER, channel);
    client->pushMessage(msg);
}