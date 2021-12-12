#include <Errors.h>
#include "messages/RawMessage.h"
#include "commands/User.h"
#include "commands/CommonReplies.h"

bool User::run(Client *client, InMessage *message) {
    const std::vector<string> params = message->getParams();
    if (params.size() < 4) {
        sendErrNeedMoreParams(client, message->getCommand());
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

void User::sendErrNeedMoreParams(Client *client, const string& command) {
    RawMessage *msg = new RawMessage(":%s %03d %s %s :Not enough parameters", client->getHostName(),
                                     ERR_NEEDMOREPARAMS, client->getNick().c_str(), command.c_str());
    client->pushMessage(msg);
}