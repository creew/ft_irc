#include <StringUtils.h>
#include "Channel.h"

using namespace std;

Channel::Channel(char *name) {
    this->name = StringUtils::duplicateString(name);
}

Channel::~Channel() {
    delete this->name;
    for (vector<char *>::iterator it = banned.begin(); it != banned.end(); it++) {
        delete (*it);
    }
    banned.clear();
    for (vector<char *>::iterator it = operators.begin(); it != operators.end(); it++) {
        delete (*it);
    }
    operators.clear();
}
