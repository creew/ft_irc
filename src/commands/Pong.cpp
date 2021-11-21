#include "commands/Pong.h"

bool Pong::run(IClient *client, InMessage *message) {
    return false;
}

const char *Pong::getName() {
    return "PONG";
}
