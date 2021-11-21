#include <Errors.h>
#include <RawMessage.h>
#include "commands/User.h"
#include "CommonReplies.h"

bool User::run(IClient *client, InMessage *message) {
    const std::vector<char *>& params = message->getParams();
    if (params.size() < 4) {
        sendErrNeedMoreParams(client, message->getCommand());
        return false;
    }
    client->setUser(params.at(0));
    if (client->getNick()) {
        CommonReplies::sendRplWelcome(client);
    }
    return false;
}

const char *User::getName() {
    return "USER";
}

void User::sendErrNeedMoreParams(IClient *client, const char *command) {
    RawMessage *msg = new RawMessage(":%s %03d %s %s :Not enough parameters", client->getHostName(),
                                     ERR_NEEDMOREPARAMS, client->getNick(), command);
    client->pushMessage(msg);
}