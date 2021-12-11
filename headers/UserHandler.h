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
    void removeClient(int fd);
    void sendMessages(int fd);
    int fillPoll(struct pollfd * polls, int maxSize, short events);
    bool sendMessageToUser(Client *clientFrom, string &user, string &message);
};


#endif //FT_IRC_USERHANDLER_H
