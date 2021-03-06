#ifndef FT_IRC_USERHANDLER_H
#define FT_IRC_USERHANDLER_H


#include "Client.h"
#include "Server.h"
#include <sys/poll.h>

class Server;
class UserHandler {
private:
    vector<Client *> clients;

public:
    virtual ~UserHandler();

    void joinUser(Client *client);
    Client *findClientByFd(int fd);
    Client *findClientByNick(string &nick);
    void removeClient(int fd);
    void sendMessages(int fd);
    int fillPoll(struct pollfd * polls, int maxSize, short events);
    bool sendMessageToUser(Client *clientFrom, const string &type, const string &user, const string &message);
};


#endif //FT_IRC_USERHANDLER_H
