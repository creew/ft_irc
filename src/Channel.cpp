#include <cstdio>
#include <Channel.h>
#include "ChannelModeHandler.h"

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

bool Channel::modifyOps(Client *client, bool add) {
    for (vector<Client *>::iterator iu = ops.begin(); iu != ops.end(); iu++) {
        if ((*iu) == client) {
            if (add) {
                return false;
            } else {
                ops.erase(iu--);
                return true;
            }
        }
    }
    if (add) {
        ops.push_back(client);
        return true;
    } else {
        return false;
    }
}

bool Channel::modifyVoiced(Client *client, bool add) {
    for (vector<Client *>::iterator iu = voiced.begin(); iu != voiced.end(); iu++) {
        if ((*iu) == client) {
            if (add) {
                return false;
            } else {
                voiced.erase(iu--);
                return true;
            }
        }
    }
    if (add) {
        voiced.push_back(client);
        return true;
    } else {
        return false;
    }
}

Channel::~Channel() {
    for (vector<IChannelMode *>::iterator ic = channelModes.begin(); ic != channelModes.end(); ic++) {
        IChannelMode *iChannelMode = *ic;
        delete iChannelMode;
    }
    channelModes.clear();
}


/**
 *
 * @param mode:
 * p - privateChannel
 * s - secretChannel
 * i - inviteOnlyChannel
 * t - topicSettableOnlyOps
 * n - noMessagesOutside
 * m - moderatedChannes
 * @return
 */
bool Channel::isModeActive(char mode) {
    for (vector<IChannelMode *>::iterator ic = channelModes.begin(); ic != channelModes.end(); ic++) {
        IChannelMode *iChannelMode = *ic;
        if (mode == iChannelMode->getName()) {
            return true;
        }
    }
    return false;
}

bool Channel::setMode(ChannelModeHandler *channelModeHandler, char mode, bool add) {
    IChannelMode *channelMode = channelModeHandler->findByMode(mode);
    if (channelMode == NULL) {
        return false;
    }
    return channelModeHandler->changeMode(channelModes, channelMode, add);
}
