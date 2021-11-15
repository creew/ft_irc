//
// Created by Алексей on 15.11.2021.
//

#ifndef FT_IRC_OUTMESSAGE_H
#define FT_IRC_OUTMESSAGE_H


class OutMessage {
private:
    char *message;
    int length;
public:
    OutMessage(const char *format, ...);

    virtual ~OutMessage();

    char *getMessage() const {
        return message;
    }

    int getLength() const {
        return length;
    }

    void reduceLength(long reduce);
};


#endif //FT_IRC_OUTMESSAGE_H
