#ifndef FT_IRC_NOMESSAGEOUTSIDECHANNELMODE_H
#define FT_IRC_NOMESSAGEOUTSIDECHANNELMODE_H


#include "IChannelMode.h"

class NoMessageOutsideChannelMode : public IChannelMode {
    char getName() {
        return 'n';
    }
};


#endif //FT_IRC_NOMESSAGEOUTSIDECHANNELMODE_H
