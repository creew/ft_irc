#include <iostream>
#include "commands/Join.h"
#include "commands/Ping.h"
#include "commands/List.h"
#include "commands/Nick.h"
#include "commands/Pass.h"
#include "commands/Pong.h"
#include "commands/User.h"
#include "commands/Quit.h"
#include "commands/Privmsg.h"
#include "StringUtils.h"
#include "CommandProcessor.h"
#include "commands/Mode.h"
#include "commands/Part.h"
#include "commands/Topic.h"
#include "commands/Who.h"
#include "commands/Names.h"

bool CommandProcessor::processAction(char *command, Client *client) {
    InMessage *message = new InMessage(command);
    if (!message->getCommand().empty()) {
        for (vector<ICommand *>::iterator ic = commands.begin(); ic != commands.end(); ic++) {
            if (StringUtils::strcmpNoCase((*ic)->getName(), message->getCommand().c_str()) == 0) {
                return (*ic)->run(client, message);
            }
        }
        cout << "Unknown command: " << message->getCommand() << endl;
    } else {
        cout << "Empty command" << endl;
    }
    return false;
}

CommandProcessor::CommandProcessor() {
    commands.push_back(new Join());
    commands.push_back(new List());
    commands.push_back(new Mode());
    commands.push_back(new Names());
    commands.push_back(new Nick());
    commands.push_back(new Part());
    commands.push_back(new Pass());
    commands.push_back(new Ping());
    commands.push_back(new Pong());
    commands.push_back(new Privmsg());
    commands.push_back(new Quit());
    commands.push_back(new Topic());
    commands.push_back(new User());
    commands.push_back(new Who());
}

CommandProcessor::~CommandProcessor() {
    for (std::vector<ICommand *>::iterator ic = commands.begin(); ic != commands.end(); ic++) {
        delete (*ic);
        commands.erase(ic--);
    }
}
