#include "ChannelModeHandler.h"
#include "channelmode/SecretChannelMode.h"
#include "channelmode/InviteOnlyChannelMode.h"
#include "channelmode/ModeratedChannelMode.h"
#include "channelmode/TopicSettableChannelMode.h"
#include "channelmode/NoMessageOutsideChannelMode.h"
#include "channelmode/PrivateChannelMode.h"

ChannelModeHandler::ChannelModeHandler() {
    channelModes.push_back(new InviteOnlyChannelMode());
    channelModes.push_back(new ModeratedChannelMode());
    channelModes.push_back(new NoMessageOutsideChannelMode());
    channelModes.push_back(new PrivateChannelMode());
    channelModes.push_back(new SecretChannelMode());
    channelModes.push_back(new TopicSettableChannelMode());
}

ChannelModeHandler::~ChannelModeHandler() {
    for (vector<IChannelMode *>::iterator ic = channelModes.begin(); ic != channelModes.end(); ic++) {
        delete *ic;
        channelModes.erase(ic--);
    }
}

IChannelMode *ChannelModeHandler::findByMode(char mode) {
    for (vector<IChannelMode *>::iterator ic = channelModes.begin(); ic != channelModes.end(); ic++) {
        IChannelMode *channelMode = *ic;
        if (channelMode->getName() == mode) {
            return channelMode;
        }
    }
    return NULL;
}

bool ChannelModeHandler::changeMode(vector<IChannelMode *> &modes, IChannelMode *mode, bool add) {
    for (vector<IChannelMode *>::iterator ic = modes.begin(); ic != modes.end(); ic++) {
        IChannelMode *channelMode = *ic;
        if (channelMode == mode) {
            if (add) {
                return false;
            } else {
                modes.erase(ic--);
                return true;
            }
        }
    }
    if (add) {
        modes.push_back(mode);
        return true;
    } else {
        return false;
    }
}

