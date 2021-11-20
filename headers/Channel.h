#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <vector>

using namespace std;

class Channel {
private:
    char *name;
    vector<char *> banned;
    vector<char *> operators;
public:
    char *getName() const {
        return name;
    }

    const vector<char *> &getBanned() const {
        return banned;
    }

    const vector<char *> &getOperators() const {
        return operators;
    }

    virtual ~Channel();

    Channel(char *name);
};


#endif //FT_IRC_CHANNEL_H
