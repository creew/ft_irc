#include "commands/Who.h"
#include "commands/CommonReplies.h"

bool Who::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNoSuchServer(client, message->getCommand());
        return false;
    }
    string param = message->getParams().at(0);
    Channel *channel = client->getChannelHandler()->findChannelByName(param);
    if (channel == NULL) {

    }

    RawMessage *msg = new RawMessage(":%s %03d %s :No topic is set", client->getHostName(), RPL_WHOREPLY, channel);
    client->pushMessage(msg);


    return false;
}

const char *Who::getName() {
    return "WHO";
}
