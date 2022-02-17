#ifndef FT_IRC_NOTICE_H
#define FT_IRC_NOTICE_H


#include "Client.h"

class Notice : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();

};


#endif //FT_IRC_NOTICE_H
