#include "commands/Who.h"
#include "commands/CommonReplies.h"

bool Who::run(Client *client, InMessage *message) {
    if (message->getParams().empty() || message->getParams().at(0).empty()) {
        CommonReplies::sendNoSuchServer(client, message->getCommand());
        return false;
    }
    string param = message->getParams().at(0);
    Channel *channel = client->getChannelHandler()->findChannelByName(param);
    if (channel != NULL) {
        vector<Client *> users = channel->getUsers();
        for (std::vector<Client *>::iterator ic = users.begin(); ic != users.end(); ic++) {
            Client *cl = *ic;
            // irc.ircnet.su 352 tre #hh kvirc 195.133.239.83 irc.ircnet.su asa H :0 KVIrc 5.0.0 Aria http://kvirc.net/
            RawMessage *msg = new RawMessage(":%s %03d %s %s %s %s %s %s H :0 %s", client->getHostName(), RPL_WHOREPLY,
                                             client->getNick().c_str(), param.c_str(), cl->getUser().c_str(), cl->getHost().c_str(),
                                             cl->getHostName(), cl->getNick().c_str(), cl->getRealName().c_str());
            client->pushMessage(msg);
        }
    }
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_ENDOFWHO,client->getNick().c_str(),
                                     "%s :End of /WHO list.", channel);
    client->pushMessage(msg);
    return false;
}

const char *Who::getName() {
    return "WHO";
}
