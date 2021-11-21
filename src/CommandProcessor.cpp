#include <stdexcept>
#include <iostream>
#include <commands/Ping.h>
#include <commands/List.h>
#include <commands/Nick.h>
#include <commands/Pass.h>
#include <commands/Pong.h>
#include <commands/User.h>
#include <commands/Quit.h>
#include <StringUtils.h>
#include "CommandProcessor.h"

bool CommandProcessor::processAction(char *command, IClient *client) {
    InMessage *message = new InMessage(command);
    if (message->getCommand() != NULL) {
        for (std::vector<ICommand *>::iterator ic = commands.begin(); ic != commands.end(); ic++) {
            if (StringUtils::strcmpNoCase((*ic)->getName(), message->getCommand()) == 0) {
                return (*ic)->run(client, message);
            }
        }
        std::cout << "Unknown command: " << message->getCommand() << std::endl;
    } else {
        std::cout << "Empty command" << std::endl;
    }
    return false;
}

CommandProcessor::CommandProcessor() {
    commands.push_back(new List());
    commands.push_back(new Nick());
    commands.push_back(new Pass());
    commands.push_back(new Ping());
    commands.push_back(new Pong());
    commands.push_back(new Quit());
    commands.push_back(new User());
}

CommandProcessor::~CommandProcessor() {
    for (std::vector<ICommand *>::iterator ic = commands.begin(); ic != commands.end(); ic++) {
        delete (*ic);
        commands.erase(ic--);
    }
}
