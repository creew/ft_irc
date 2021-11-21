#include "commands/Quit.h"

bool Quit::run(IClient *client, InMessage *message) {
    return true;
}

const char *Quit::getName() {
    return "QUIT";
}
