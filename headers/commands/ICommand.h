#ifndef FT_IRC_ICOMMAND_H
#define FT_IRC_ICOMMAND_H

#include <InMessage.h>
#include <IClient.h>

class ICommand {
public:
    virtual void run(IClient *client, InMessage *message) = 0;

    virtual const char *getName() = 0;

    virtual ~ICommand() {};
};


#endif //FT_IRC_ICOMMAND_H
