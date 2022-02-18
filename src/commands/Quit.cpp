#include "commands/Quit.h"

bool Quit::run(Client *client, InMessage *message) {
    (void) client;
    (void) message;
    return true;
}

const char *Quit::getName() {
    return "QUIT";
}
