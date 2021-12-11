#include "commands/Pass.h"

bool Pass::run(Client *client, InMessage *message) {
    const char *serverPassword = client->getServerPassword();
    if (serverPassword) {
        if (!message->getParams().empty()) {
            if (strcmp(message->getParams().at(0).c_str(), serverPassword) == 0) {
                client->setOpMode(true);
            }
        }
    }
    return false;
}

const char *Pass::getName() {
    return "PASS";
}
