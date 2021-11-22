#include "commands/Pong.h"

bool Pong::run(Client *client, InMessage *message) {
    return false;
}

const char *Pong::getName() {
    return "PONG";
}
