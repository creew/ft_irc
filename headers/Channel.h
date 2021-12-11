#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <vector>
#include <string>

using namespace std;

class Client;

class Channel {
private:
    string name;
    string topic;
    vector<Client *> users;
    bool privateChannel;  //p
    bool secretChannel;  //s
    bool inviteOnlyChannel;  //i
    bool topicSettable;  //t
    bool noMessagesOutside;  //n
    bool moderatedChannel;  //m
    vector<Client *> ops;
    vector<Client *> voiced;
public:
    explicit Channel(const string &name) : name(name), privateChannel(false), secretChannel(false),
                                           inviteOnlyChannel(false),
                                           topicSettable(true), noMessagesOutside(true), moderatedChannel(false) {}

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

    bool isPrivateChannel() const {
        return privateChannel;
    }

    void setPrivateChannel(bool privateChannel) {
        Channel::privateChannel = privateChannel;
    }

    bool isSecretChannel() const {
        return secretChannel;
    }

    void setSecretChannel(bool secretChannel) {
        Channel::secretChannel = secretChannel;
    }

    bool isInviteOnlyChannel() const {
        return inviteOnlyChannel;
    }

    void setInviteOnlyChannel(bool inviteOnlyChannel) {
        Channel::inviteOnlyChannel = inviteOnlyChannel;
    }

    bool isTopicSettable() const {
        return topicSettable;
    }

    void setTopicSettable(bool topicSettable) {
        Channel::topicSettable = topicSettable;
    }

    bool isNoMessagesOutside() const {
        return noMessagesOutside;
    }

    void setNoMessagesOutside(bool noMessagesOutside) {
        Channel::noMessagesOutside = noMessagesOutside;
    }

    bool isModeratedChannel() const {
        return moderatedChannel;
    }

    void setModeratedChannel(bool moderatedChannel) {
        Channel::moderatedChannel = moderatedChannel;
    }

    bool putUser(Client *pClient);

    void addToOps(Client *client);
};


#endif //FT_IRC_CHANNEL_H
