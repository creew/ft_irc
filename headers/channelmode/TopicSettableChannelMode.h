#ifndef FT_IRC_TOPICSETTABLECHANNELMODE_H
#define FT_IRC_TOPICSETTABLECHANNELMODE_H


#include "IChannelMode.h"

class TopicSettableChannelMode : public IChannelMode {
    char getName() {
        return 't';
    }
};


#endif //FT_IRC_TOPICSETTABLECHANNELMODE_H
