#ifndef FT_IRC_COMMANDPROCESSOR_H
#define FT_IRC_COMMANDPROCESSOR_H

#include <cstdio>
#include <commands/ICommand.h>
#include "ServerConfiguration.h"
#include "IClient.h"
#include "InMessage.h"

class CommandProcessor {
    vector<ICommand *> commands;
public:
    CommandProcessor();

    bool processAction(char *message, IClient *client);

    virtual ~CommandProcessor();
};


#endif //FT_IRC_COMMANDPROCESSOR_H
