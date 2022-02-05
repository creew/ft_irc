#include <iostream>
#include "UserHandler.h"
#include "messages/ClientRawMessage.h"

UserHandler::~UserHandler() {
    for (vector<Client *>::iterator ic = clients.begin(); ic != clients.end(); ic++) {
        delete *ic;
        clients.erase(ic--);
    }
}

void UserHandler::joinUser(Client *client) {
    clients.push_back(client);
}

Client *UserHandler::findClientByFd(int fd) {
    for (vector<Client *>::iterator client = clients.begin(); client != clients.end(); client++) {
        if ((*client)->getFd() == fd) {
            return *client;
        }
    }
    return NULL;
}

void UserHandler::removeClient(int fd) {
    for (vector<Client *>::iterator client = clients.begin(); client != clients.end(); client++) {
        if ((*client)->getFd() == fd) {
            delete *client;
            clients.erase(client--);
            return;
        }
    }
}

void UserHandler::sendMessages(int fd) {
    for (vector<Client *>::iterator ic = clients.begin(); ic != clients.end(); ic++) {
        Client *client = *ic;
        if (client->getFd() == fd) {
            client->sendMessages();
        }
    }
}

int UserHandler::fillPoll(struct pollfd *polls, int maxSize, short events) {
    int i = 0;
    for (vector<Client *>::iterator client = clients.begin(); client != clients.end(); client++) {
        if (i >= maxSize) {
            cerr << "Maximum number of clients reached";
            break;
        }
        polls[i].fd = (*client)->getFd();
        polls[i++].events = events;
    }
    return i;
}

bool UserHandler::sendMessageToUser(Client *clientFrom, string &user, string &message) {
    for (vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
        Client *clientTo = *it;
        if (user == clientTo->getNick()) {
            RawMessage *msg = new ClientRawMessage(clientFrom, "PRIVMSG %s :%s", user.c_str(), message.c_str());
            clientTo->pushMessage(msg);
            return true;
        }
    }
    return false;
}

Client *UserHandler::findClientByNick(string &nick) {
    for (vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
        Client *clientTo = *it;
        if (nick == clientTo->getNick()) {
            return clientTo;
        }
    }
    return NULL;
}
