#ifndef FT_IRC_ISERVER_H
# define FT_IRC_ISERVER_H

#include "Channel.h"
#include "CommandProcessor.h"

class IServer {
public:
    virtual ~IServer() {}

    virtual const vector<Channel *> &getChannels() const = 0;

    virtual CommandProcessor *getCommandProcessor() const = 0;

    virtual void removeClientFromChannel(IClient *client) = 0;

    virtual const ServerConfiguration *getConfiguration() const = 0;
};

#endif