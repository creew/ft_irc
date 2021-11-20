#ifndef FT_IRC_LIST_H
#define FT_IRC_LIST_H

#include "ICommand.h"

class List : public ICommand{
    void run(IClient *client, InMessage *message);

    const char *getName();

private:
    void sendRplListStart(IClient *client);
    void sendRplList(IClient *client);
    void sendRplEnd(IClient *client);
};

#endif //FT_IRC_LIST_H
