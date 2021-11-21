#include "commands/Pass.h"

bool Pass::run(IClient *client, InMessage *message) {
    const char *serverPassword = client->getServerPassword();
    if (serverPassword) {
        if (!message->getParams().empty()) {
            if (strcmp(message->getParams().at(0), serverPassword) != 0) {

            }
        }
    }
    return false;
}

const char *Pass::getName() {
    return "PASS";
}
