//
// Created by Edythe Klompus on 11/13/21.
//

#include <stdexcept>
#include <cstring>
#include <iostream>
#include "CommandProcessor.h"
#include "ServerConfiguration.h"

const CommandAction CommandProcessor::actions[] = {
        {"PASS", passAction},
        {"USER", nickAction},
        {"NICK", userAction}
};


void CommandProcessor::processAction(char *command, const Configuration *configuration) {
    while (*command == ' ') {
        command++;
    }
    char *action = command;
    while (*command != ' ' && *command != '\0') {
        command++;
    }
    if (*command == '\0') {
        throw std::invalid_argument("invalid command");
    }
    *command++ = '\0';
    while (*command == ' ') {
        command++;
    }
    for (int i = 0; i < sizeof(CommandProcessor::actions) / sizeof(CommandProcessor::actions[0]); i++) {
        if (strcmp(actions[i].command, action) == 0) {
            if (actions[i].action) {
                actions[i].action(command, configuration);
                return;
            }
        }
    }
    std::cout << "Unknown action: " << action << std::endl;
}

void CommandProcessor::passAction(char *command, const Configuration *configuration) {
    if (strcmp(command, configuration->password.c_str()) != 0) {

    }
}

void CommandProcessor::nickAction(char *command, const Configuration *configuration) {

}

void CommandProcessor::userAction(char *command, const Configuration *configuration) {

}
