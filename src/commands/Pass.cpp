#include "commands/Pass.h"

bool Pass::run(Client *client, InMessage *message) {
    string serverPassword = client->getServerPassword();
    if (!serverPassword.empty()) {
        if (!message->getParams().empty()) {
            if (message->getParams().at(0) == serverPassword) {
                client->setOpMode(true);
            }
        }
    }
    return false;
}

const char *Pass::getName() {
    return "PASS";
}
