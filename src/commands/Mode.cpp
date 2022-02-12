#include "commands/Mode.h"
#include "commands/CommonReplies.h"

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
        parseArgs(channel, params, 1);
    }
}

void Mode::sendCurrentMode(Channel *channel, Client *client) {

    string mode = "+";
    vector<IChannelMode *> modes = channel->getChannelModes();
    for (vector<IChannelMode *>::iterator ic = modes.begin(); ic != modes.end(); ic++) {
        mode.append((*ic)->getName());
    }
    RawMessage *msg = new RawMessage(client->getHostName(), RPL_CHANNELMODEIS,
                                     client->getNick().c_str(), "%s %s", channel->getName().c_str(), mode.c_str());
    client->pushMessage(msg);
}

void Mode::parseArgs(Channel *channel, const vector<string> &params, int startPos) {
    while (startPos < params.size()) {
        string arg = params.at(startPos);
        startPos++;
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
                    channel.setMode('p');
                    break;
            }
        }



    }
}

const char *Mode::getName() {
    return "MODE";
}


