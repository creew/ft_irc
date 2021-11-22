
#include <cstdio>
#include <Channel.h>


void Channel::removeUser(Client *user) {
    for (vector<Client *>::iterator iu = users.begin(); iu != users.end(); iu++) {
        if ((*iu) == user) {
            users.erase(iu--);
        }
    }
}

size_t Channel::usersCount() {
    return users.size();
}

bool Channel::putUser(Client *client) {
    users.push_back(client);
    return true;
}
