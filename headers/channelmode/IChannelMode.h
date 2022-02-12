#ifndef FT_IRC_ICHANNELMODE_H
#define FT_IRC_ICHANNELMODE_H


class IChannelMode {
public:
    virtual char getName() = 0;

    virtual ~IChannelMode() {};
};


#endif //FT_IRC_ICHANNELMODE_H
