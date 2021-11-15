//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_COMMANDPROCESSOR_H
#define FT_IRC_COMMANDPROCESSOR_H

#include <cstdio>
#include "ServerConfiguration.h"
#include "Client.h"
#include "Message.h"

typedef void (*t_action)(Message *message, Client *client);

struct CommandAction
{
    const char *command;
    t_action action;
};

class CommandProcessor {
private:
    CommandProcessor() {}
    static const CommandAction actions[];
    static void passAction(Message *message, Client *client);
    static void nickAction(Message *message, Client *client);
    static void userAction(Message *message, Client *client);
public:
    static void processAction(char *message, Client *client);

    static void emptyAction(Message *message, Client *client);

    static void listChannels(Message *message, Client *client);

    static void pingAction(Message *message, Client *client);
};


#endif //FT_IRC_COMMANDPROCESSOR_H
