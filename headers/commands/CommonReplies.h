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

    static void sendNoSuchNickOrChannel(Client *client, const string &nick);

    static void sendNotOnChannel(Client *client, const string &channel);

    static void sendNotChannelOperator(Client *client, const string &channel);

    static void sendNoSuchServer(Client *client, const string &channel);

    static void sendNoNickNameGiven(Client *client);

    static void sendNickNameInUse(Client *client, string &nick);

    static void sendTheyAreNotOnThatChannel(Client *client, const string &channelName, const string &nickName);

    static void sendAllChannelUsers(Client *client, Channel *channel, RawMessage *message);
};


#endif //FT_IRC_COMMONREPLIES_H
