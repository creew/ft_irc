#ifndef FT_IRC_TOPICSETTABLECHANNELMODE_H
#define FT_IRC_TOPICSETTABLECHANNELMODE_H


#include "IChannelMode.h"

class TopicSettableChannelMode : public IChannelMode {
    const char *getName() {
        return "s";
    }
};


#endif //FT_IRC_TOPICSETTABLECHANNELMODE_H
