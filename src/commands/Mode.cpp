#include "commands/Mode.h"
#include "commands/CommonReplies.h"
#include "messages/ClientRawMessage.h"

bool Mode::run(Client *client, InMessage *message) {
    if (!message->getParams().empty()) {
        string val = message->getParams().at(0);
        if (isChannel(val)) {
            processChannel(client, val, message->getParams());
        } else {
            processNick(client, val, message->getParams());
        }
    }
    return false;
}

void Mode::processNick(Client *client, const string &nickName, const vector<string> &params) {
}

void Mode::processChannel(Client *client, const string &channelName, const vector<string> &params) {
    Channel *channel = client->getChannelHandler()->findChannelByName(channelName);
    if (channel == NULL) {
        CommonReplies::sendNoSuchChannel(client, channelName);
        return;
    }
    if (params.size() == 1) {
        sendCurrentMode(channel, client);
    } else {
        parseArgs(client, channel, params, 1);
    }
}

void Mode::sendCurrentMode(Channel *channel, Client *client) {
    string mode = "+";
    vector<IChannelMode *> modes = channel->getChannelModes();
    for (vector<IChannelMode *>::iterator ic = modes.begin(); ic != modes.end(); ic++) {
        mode.append(string(1, (*ic)->getName()));
    }
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_CHANNELMODEIS,
                                     client->getNick().c_str(), "%s %s", channel->getName().c_str(), mode.c_str());
    client->pushMessage(msg);
}

void Mode::parseArgs(Client *client, Channel *channel, const vector<string> &params, int startPos) {
    string addPerm = "+";
    string removePerm = "-";
    while (startPos < params.size()) {
        string arg = params.at(startPos++);
        bool add = true;
        for (std::string::size_type i = 0; i < arg.size(); i++) {
            switch (arg[i]) {
                case '+':
                    add = true;
                    break;
                case '-':
                    add = false;
                    break;
                case 'p':
                case 's':
                case 'i':
                case 't':
                case 'n':
                case 'm':
                    if (!channel->isUserOps(client)) {
                        CommonReplies::sendNotChannelOperator(client, channel->getName());
                        return;
                    }
                    if (channel->setMode(client->getChannelModeHandler(), arg[i], add)) {
                        if (add) {
                            addPerm.append(string(1, arg[i]));
                        } else {
                            removePerm.append(string(1, arg[i]));
                        }
                    }
                    break;
                case 'o':
                    if (!channel->isUserOps(client)) {
                        CommonReplies::sendNotChannelOperator(client, channel->getName());
                        return;
                    }
                    if (startPos < params.size()) {
                        string nick = params.at(startPos++);
                        Client * adds = client->getUserHandler()->findClientByNick(nick);
                        if (adds == NULL) {
                            CommonReplies::sendNoSuchNickOrChannel(client, nick);
                            break;
                        }
                        if (!channel->isUserOnChannel(adds)) {
                            CommonReplies::sendTheyAreNotOnThatChannel(client, channel->getName(), nick);
                            break;
                        }
                        RawMessage *message = new ClientRawMessage(client, "MODE %s %so %s", channel->getName().c_str(), add ? "+" : "-", nick.c_str());
                        CommonReplies::sendAllChannelUsers(client, channel->getName(), message);
                        if (add) {
                            channel->addToOps(adds);
                        } else {
                            channel->removeFromOps(adds);
                        }
                    }
                    break;
            }
        }
    }
    if (addPerm.size() > 1 || removePerm.size() > 1) {
        RawMessage *message = new ClientRawMessage(client, "MODE %s %s%s", channel->getName().c_str(), addPerm.c_str(), removePerm.c_str());
        CommonReplies::sendAllChannelUsers(client, channel->getName(), message);
    }
}

const char *Mode::getName() {
    return "MODE";
}


