#ifndef FT_IRC_COMMONREPLIES_H
#define FT_IRC_COMMONREPLIES_H

#include <IClient.h>

class CommonReplies {
private:
    CommonReplies() {}
public:
    static void sendRplWelcome(IClient *client);
    static void sendRplYourHost(IClient *client);
    static void sendRplCreated(IClient *client);
    static void sendRplMyInfo(IClient *client);
};


#endif //FT_IRC_COMMONREPLIES_H
