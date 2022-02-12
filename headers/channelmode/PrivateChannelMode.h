#ifndef FT_IRC_PRIVATECHANNELMODE_H
#define FT_IRC_PRIVATECHANNELMODE_H


#include <clocale>
#include "IChannelMode.h"

class PrivateChannelMode : public IChannelMode {
    const char *getName() {
        return "p";
    }
};


#endif //FT_IRC_PRIVATECHANNELMODE_H
