#include <iostream>
#include "commands/Names.h"
#include "messages/ServerRawMessage.h"

bool Names::run(Client *client, InMessage *message) {
    if (message->getParams().empty()) {

    } else {
        string param = message->getParams().at(0);
        int startPos = 0, endPos;
        string channel;
        while ((endPos = param.find(',', startPos)) != std::string::npos) {
            channel = param.substr(startPos, endPos - startPos);
            std::cout << channel << std::endl;
            sendChannelUsers(client, channel);
            startPos = endPos + 1;
        }
        channel = param.substr(startPos);
        sendChannelUsers(client, channel);
    }
    return false;
}

const char *Names::getName() {
    return "NAMES";
}

void Names::sendChannelUsers(Client *client, const string &channelName) {
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel != NULL && !channel->isModeActive("s") && !channel->isModeActive("p")) {
        vector<Client *> clients = channel->getUsers();
        if (!clients.empty()) {
            Client *iClient = *clients.begin();
            ServerRawMessage *msg = new ServerRawMessage(":%s %03d %s = %s :", client->getHostName(), RPL_NAMREPLY,
                                                         client->getNick().c_str(), channelName.c_str());
            addUser(msg, channel, iClient);
            for (vector<Client *>::iterator iu = clients.begin() + 1; iu != clients.end(); iu++) {
                iClient = *iu;
                msg->addConst(" ");
                addUser(msg, channel, iClient);
            }
            msg->finalize();
            client->pushMessage(msg);
        }
    }
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_ENDOFNAMES, client->getNick().c_str(),
                                     "%s :End of /NAMES list", channelName.c_str());
    client->pushMessage(msg);

}

void Names::addUser(ServerRawMessage *msg, Channel *channel, Client *client) {
    if (channel->isUserOps(client)) {
        msg->addConst("@");
    } else if (channel->isUserVoiced(client)) {
        msg->addConst("+");
    }
    msg->copy(client->getNick().c_str());
}