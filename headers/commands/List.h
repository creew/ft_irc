#ifndef FT_IRC_LIST_H
#define FT_IRC_LIST_H

#include "ICommand.h"

class List : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();

private:
    void sendRplListStart(Client *client);
    void sendRplList(Client *client);
    void sendRplEnd(Client *client);
};

#endif //FT_IRC_LIST_H
