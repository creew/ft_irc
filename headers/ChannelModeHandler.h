#ifndef FT_IRC_CHANNELMODEHANDLER_H
#define FT_IRC_CHANNELMODEHANDLER_H

#include <string>
#include <vector>
#include "channelmode/IChannelMode.h"

using namespace std;

class ChannelModeHandler {
private:
    vector<IChannelMode *> channelModes;
public:
    ChannelModeHandler();

    virtual ~ChannelModeHandler();

    IChannelMode *findByMode(char mode);

    bool changeMode(vector<IChannelMode *> &channelModes, IChannelMode *mode, bool add);
};


#endif //FT_IRC_CHANNELMODEHANDLER_H
