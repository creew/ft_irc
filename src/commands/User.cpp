#include "commands/User.h"
#include "commands/CommonReplies.h"

bool User::run(Client *client, InMessage *message) {
    const std::vector<string> params = message->getParams();
    if (params.size() < 4) {
        CommonReplies::sendNeedMoreParams(client, message->getCommand());
        return false;
    }
    client->setUser(params.at(0));
    client->setRealName(params.at(3));
    if (!client->getNick().empty()) {
        CommonReplies::sendRplWelcome(client);
    }
    return false;
}

const char *User::getName() {
    return "USER";
}
