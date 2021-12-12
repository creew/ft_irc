#ifndef FT_IRC_CLIENTRAWMESSAGE_H
#define FT_IRC_CLIENTRAWMESSAGE_H

#include "Client.h"
#include "RawMessage.h"

#define CLIENT_MSG_PREFIX ":%s!%s@%s "

class Client;
class ClientRawMessage : public RawMessage {
public:
    ClientRawMessage(Client *client, const char *format, ...);
};


#endif //FT_IRC_CLIENTRAWMESSAGE_H
