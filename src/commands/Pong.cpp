#include <RawMessage.h>
#include "commands/Pong.h"

void Pong::run(IClient *client, InMessage *message) {
}

const char *Pong::getName() {
    return "PONG";
}
