#ifndef FT_IRC_ICLIENT_H
# define FT_IRC_ICLIENT_H

#include "Channel.h"
#include "RawMessage.h"

using namespace std;

class IClient {
public:
    virtual ~IClient() {}

    virtual int getFd() const = 0;

    virtual bool processData(const char *data, size_t length) = 0;

    virtual const char *getServerPassword() = 0;

    virtual void setNick(const char *string) = 0;

    virtual void setUser(const char *user) = 0;

    virtual char *getUser() const = 0;

    virtual char *getNick() const = 0;

    virtual void pushMessage(RawMessage *outMessage) = 0;

    virtual vector<RawMessage *> *getSendQueue() = 0;

    virtual const char *getHostName() = 0;

    virtual vector<Channel *> getChannels() = 0;
};

#endif
