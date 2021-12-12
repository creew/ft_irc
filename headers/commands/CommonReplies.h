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
    static void sendNeedMoreParams(Client *client, const string &command);
    static void sendNoRecipientGiven(Client *client, const string &command);
    static void sendNoTextToSend(Client *client);
    static void sendNoSuchChannel(Client *client, const string &channel);

    static void sendNotOnChannel(Client *client, const string &channel);

    static void sendNotChannelOperator(Client *client, const string &channel);

    static void sendNoSuchServer(Client *client, const string &channel);
};


#endif //FT_IRC_COMMONREPLIES_H
