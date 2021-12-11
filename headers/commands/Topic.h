#ifndef FT_IRC_TOPIC_H
#define FT_IRC_TOPIC_H


#include "ICommand.h"

class Topic : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();

    static void sendNoTopic(Client *client, const char *channel);

    static void sendTopic(Client *client, const char *channel, const char *topic);
};


#endif //FT_IRC_TOPIC_H
