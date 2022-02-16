#ifndef FT_IRC_SECRETCHANNELMODE_H
#define FT_IRC_SECRETCHANNELMODE_H


#include "IChannelMode.h"

class SecretChannelMode : public IChannelMode {
    char getName() {
        return 's';
    }
};


#endif //FT_IRC_SECRETCHANNELMODE_H
