//
// Created by Edythe Klompus on 11/13/21.
//

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "CommandProcessor.h"
#include "ServerConfiguration.h"
#include "Message.h"

const CommandAction CommandProcessor::actions[] = {
        {"PASS", passAction},
        {"USER", userAction},
        {"NICK", nickAction}
};


void CommandProcessor::processAction(char *command, Client *client) {
    Message message;
    message.parseMessage(command);
    if (message.getCommand() != NULL) {
        for (int i = 0; i < sizeof(CommandProcessor::actions) / sizeof(CommandProcessor::actions[0]); i++) {
            if (strcmp(actions[i].command, message.getCommand()) == 0) {
                if (actions[i].action) {
                    actions[i].action(&message, client);
                    return;
                }
            }
        }
        std::cout << "Unknown command: " << message.getCommand() << std::endl;
    } else {
        std::cout << "Empty command" << std::endl;
    }
}

void CommandProcessor::passAction(Message *message, Client *client) {
    const char *serverPassword = client->getServerPassword();
    if (serverPassword) {
        if (!message->getParams().empty()) {
            if (strcmp(message->getParams().at(0), serverPassword) != 0) {

            }
        }
    }
}

void CommandProcessor::nickAction(Message *message, Client *client) {
    if (!message->getParams().empty()) {
        client->setNick(message->getParams().at(0));
    }
    client->sendRplWelcome();
}

void CommandProcessor::userAction(Message *message, Client *client) {
    const std::vector<char *>& params = message->getParams();
    if (params.size() < 4) {
        client->sendErrNeedMoreParams(message->getCommand());
        return;
    }
    client->setUser(params.at(0));
    client->sendRplWelcome();
}
