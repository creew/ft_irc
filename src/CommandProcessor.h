//
// Created by Edythe Klompus on 11/13/21.
//

#ifndef FT_IRC_COMMANDPROCESSOR_H
#define FT_IRC_COMMANDPROCESSOR_H

#include <cstdio>
#include "ServerConfiguration.h"

typedef void (*t_action)(char *command, const Configuration *configuration);

struct CommandAction
{
    char *command;
    t_action action;
};

class CommandProcessor {
private:
    CommandProcessor() {}
    static const CommandAction actions[];
    static void passAction(char *command, const Configuration *configuration);
    static void nickAction(char *command, const Configuration *configuration);
    static void userAction(char *command, const Configuration *configuration);
public:
    static void processAction(char *command, const Configuration *configuration);
};


#endif //FT_IRC_COMMANDPROCESSOR_H
