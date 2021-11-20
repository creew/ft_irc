#include "commands/Quit.h"

void Quit::run(IClient *client, InMessage *message) {

}

const char *Quit::getName() {
    return "QUIT";
}
