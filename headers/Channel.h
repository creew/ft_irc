#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <vector>
#include <string>
#include "channelmode/IChannelMode.h"
#include "ChannelModeHandler.h"

using namespace std;

class Client;

class Channel {
private:
    string name;
    string topic;
    vector<Client *> users;
    vector<IChannelMode *> channelModes;
    vector<Client *> ops;
    vector<Client *> voiced;
public:
    explicit Channel(const string &name) : name(name) { }

    virtual ~Channel();

    const string &getName() const {
        return name;
    }

    const string &getTopic() const {
        return topic;
    }

    const vector<Client *> &getUsers() const {
        return users;
    }

    void removeUser(Client *user);

    size_t usersCount();

    bool isUserOnChannel(Client *client);

    bool isUserOps(Client *client);

    bool isUserVoiced(Client *client);


    void setTopic(const string &topic) {
        Channel::topic = topic;
    }

    bool putUser(Client *pClient);

    bool addToOps(Client *client);

    bool removeFromOps(Client *client);

    bool isModeActive(char mode);

    bool setMode(ChannelModeHandler *channelModeHandler, char mode, bool add);

    const vector<IChannelMode *> &getChannelModes() const {
        return channelModes;
    }
};


#endif //FT_IRC_CHANNEL_H
