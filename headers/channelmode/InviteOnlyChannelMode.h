#ifndef FT_IRC_INVITEONLYCHANNELMODE_H
#define FT_IRC_INVITEONLYCHANNELMODE_H


#include "IChannelMode.h"

class InviteOnlyChannelMode : public IChannelMode {
    char getName() {
        return 'i';
    }
};


#endif //FT_IRC_INVITEONLYCHANNELMODE_H
