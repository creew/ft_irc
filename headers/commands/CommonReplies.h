#ifndef FT_IRC_COMMONREPLIES_H
#define FT_IRC_COMMONREPLIES_H

#include <Client.h>

class CommonReplies {
private:
    CommonReplies() {}
public:
    static void sendRplWelcome(Client *client);
    static void sendRplYourHost(Client *client);
    static void sendRplCreated(Client *client);
    static void sendRplMyInfo(Client *client);
    static void sendNotEnoughParameters(Client *client, const char *command);
    static void sendNoRecipientGiven(Client *client, const char *command);
    static void sendNoTextToSend(Client *client);
};


#endif //FT_IRC_COMMONREPLIES_H
