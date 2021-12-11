
#include <cstdio>
#include <Channel.h>


void Channel::removeUser(Client *user) {
    for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
        if ((*iu) == user) {
            users.erase(iu--);
        }
    }
    for (vector<Client *>::iterator iu = ops.begin(); iu != ops.end(); iu++) {
        if ((*iu) == user) {
            ops.erase(iu--);
        }
    }
    for (vector<Client *>::iterator iu = voiced.begin(); iu != voiced.end(); iu++) {
        if ((*iu) == user) {
            voiced.erase(iu--);
        }
    }
}

size_t Channel::usersCount() {
    return users.size();
}

bool Channel::putUser(Client *user) {
    for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
        if ((*iu) == user) {
            return false;
        }
    }
    users.push_back(user);
    return true;
}

bool Channel::isUserOnChannel(Client *client) {
    for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
        if ((*iu) == client) {
            return true;
        }
    }
    return false;
}

bool Channel::isUserOps(Client *client) {
    for (vector<Client *>::iterator iu = ops.begin(); iu != ops.end(); iu++) {
        if ((*iu) == client) {
            return true;
        }
    }
    return false;
}

bool Channel::isUserVoiced(Client *client) {
    for (vector<Client *>::iterator iu = voiced.begin(); iu != voiced.end(); iu++) {
        if ((*iu) == client) {
            return true;
        }
    }
    return false;
}

void Channel::addToOps(Client *client) {
    ops.push_back(client);
}

