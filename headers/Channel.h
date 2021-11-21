#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <vector>
#include <string>

using namespace std;

class IClient;
class Channel {
private:
    string name;
    string topic;
    vector<IClient *> users;
public:
    int getUsersCount();

    explicit Channel(const string &name) : name(name) {}

    const string &getName() const {
        return name;
    }

    const string &getTopic() const {
        return topic;
    }

    const vector<IClient *> &getUsers() const {
        return users;
    }

    void setTopic(const string &topic) {
        Channel::topic = topic;
    }
};


#endif //FT_IRC_CHANNEL_H
