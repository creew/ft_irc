#ifndef FT_IRC_COMMANDPROCESSOR_H
#define FT_IRC_COMMANDPROCESSOR_H

#include <commands/ICommand.h>
#include "Client.h"

class ICommand;
class CommandProcessor {
    vector<ICommand *> commands;
public:
    CommandProcessor();

    bool processAction(char *message, Client *client);

    virtual ~CommandProcessor();
};


#endif //FT_IRC_COMMANDPROCESSOR_H
