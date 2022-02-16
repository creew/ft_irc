#ifndef FT_IRC_MODE_H
#define FT_IRC_MODE_H


#include "commands/ICommand.h"

class Mode : public ICommand{
    bool run(Client *client, InMessage *message);

    const char *getName();
private:
    void processNick(Client *client, const string &nickName, const vector<string> &params);

    void processChannel(Client *client, const string &channelName, const vector<string> &params);

    void sendCurrentMode(Channel *channel, Client *client);

    void parseArgs(Client *client, Channel *channel, const vector<string> &params, int startPos);
};


#endif //FT_IRC_MODE_H
