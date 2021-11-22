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
    bool operatorPrivileges;  //o
    bool privateChannel;  //p
    bool secretChannel;  //s
    bool inviteOnlyChannel;  //i
    bool topicSettable;  //t
    bool noMessagesOutside;  //n
    bool banMask;  //b
    bool abilityToSpeak;  //v
public:
    explicit Channel(const string &name) : name(name) {}

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


    void setTopic(const string &topic) {
        Channel::topic = topic;
    }

    bool isOperatorPrivileges() const {
        return operatorPrivileges;
    }

    void setOperatorPrivileges(bool operatorPrivileges) {
        Channel::operatorPrivileges = operatorPrivileges;
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

    bool isBanMask() const {
        return banMask;
    }

    void setBanMask(bool banMask) {
        Channel::banMask = banMask;
    }

    bool isAbilityToSpeak() const {
        return abilityToSpeak;
    }

    void setAbilityToSpeak(bool abilityToSpeak) {
        Channel::abilityToSpeak = abilityToSpeak;
    }

    bool putUser(Client *pClient);
};


#endif //FT_IRC_CHANNEL_H
