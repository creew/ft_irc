#include "Errors.h"
#include "commands/CommonReplies.h"

void CommonReplies::sendRplWelcome(Client *client) {
    if (!client->getNick().empty() && !client->getUser().empty()) {
        RawMessage *msg = new RawMessage(client->getHostName(), RPL_WELCOME, client->getNick().c_str(),
                                         ":Welcome to the localhost IRC Network %s!%s@%s",
                                         client->getNick().c_str(), client->getUser().c_str(),
                                         client->getHost().c_str());
        client->pushMessage(msg);
        sendRplYourHost(client);
    }
}

void CommonReplies::sendRplYourHost(Client *client) {
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_YOURHOST, client->getNick().c_str(), ":Your host is %s, running version 01.000.00",
                                     "localhost");
    client->pushMessage(msg);
    sendRplCreated(client);
}

void CommonReplies::sendRplCreated(Client *client) {
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_CREATED, client->getNick().c_str(),
                                     ":This server was created 11.11.2021");
    client->pushMessage(msg);
    sendRplMyInfo(client);
}

//:server 004 <nick> <servername> <version> <available umodes> <available cmodes> [<cmodes with param>]
void CommonReplies::sendRplMyInfo(Client *client) {
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_MYINFO, client->getNick().c_str(),
                                     "ft_irc 01.000.00 io psnmtiobv",
                                     client->getNick().c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNeedMoreParams(Client *client, const string &command) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NEEDMOREPARAMS, client->getNick().c_str(),
                                     "%s :Not enough parameters", command.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNoTextToSend(Client *client) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NOTEXTTOSEND, client->getNick().c_str(),
                                     ":No text to send");
    client->pushMessage(msg);
}

void CommonReplies::sendNoRecipientGiven(Client *client, const string &command) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NORECIPIENT, client->getNick().c_str(),
                                     ":No recipient given (%s)", command.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNoSuchChannel(Client *client, const string &channel) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NOSUCHCHANNEL, client->getNick().c_str(),
                                     ":No such channel", channel.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNoSuchNickOrChannel(Client *client, const string &nick) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NOSUCHNICK, client->getNick().c_str(),
                                     ":No such nick or channel", nick.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNotOnChannel(Client *client, const string &channel) {
    RawMessage *msg = new RawMessage( client->getHostName(), ERR_NOTONCHANNEL, client->getNick().c_str(),
                                      "%s :You're not on that channel", channel.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNotChannelOperator(Client *client, const string &channel) {
    RawMessage *msg = new RawMessage( client->getHostName(), ERR_CHANOPRIVSNEEDED, client->getNick().c_str(),
                                      "%s :You're not channel operator", channel.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNoSuchServer(Client *client, const string &channel) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No such server",
                                     client->getHostName(), ERR_NOSUCHSERVER, channel.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNoNickNameGiven(Client *client) {
    RawMessage *msg = new RawMessage(":%s %03d %s :No nickname given",
                                     client->getHostName(), ERR_NONICKNAMEGIVEN, client->getUser().c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendNickNameInUse(Client *client, string &nick) {
    RawMessage *msg = new RawMessage(client->getHostName(), ERR_NICKNAMEINUSE, client->getNick().c_str(),
                                     "%s :Nickname is already in use", nick.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendTheyAreNotOnThatChannel(Client *client, const string &channelName, const string &nickName) {
    RawMessage *msg = new RawMessage(":%s %03d %s %s :They aren't on that channel",
                                     client->getHostName(), ERR_USERNOTINCHANNEL, channelName.c_str(), nickName.c_str());
    client->pushMessage(msg);
}

void CommonReplies::sendAllChannelUsers(Client *client, Channel *channel, RawMessage *message) {
    (void) client;
    vector<Client *> clients = channel->getUsers();
    for (vector<Client *>::iterator iu = clients.begin(); iu != clients.end(); iu++) {
        Client *iClient = *iu;
        iClient->pushMessage(message->clone());
    }
    delete message;
}
