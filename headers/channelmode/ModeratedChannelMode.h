#ifndef FT_IRC_MODERATEDCHANNELMODE_H
#define FT_IRC_MODERATEDCHANNELMODE_H


#include "IChannelMode.h"

class ModeratedChannelMode : public IChannelMode {
    char getName() {
        return 'm';
    }
};


#endif //FT_IRC_MODERATEDCHANNELMODE_H
