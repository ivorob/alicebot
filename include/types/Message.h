#ifndef __ALICE_BOT_MESSAGE_H__
#define __ALICE_BOT_MESSAGE_H__

#include <string>
#include <json/json.h>
#include "types/User.h"
#include "types/PhotoSize.h"
#include "types/Chat.h"

namespace bot {

class Message {
public:
    typedef std::vector<bot::PhotoSize> Photo;
public:
    Message();
    Message(const Json::Value& message);

    int getId() const;
    User getFrom() const;
    Chat getChat() const;
    const std::string& getText() const;

    const time_t& getDate() const;

    bool hasAttachments() const;
    const Photo& getPhoto() const;
private:
    void fetchPhoto(const Json::Value& photo);
private:
    int messageId;
    User from;
    Chat chat;
    std::string text;
    time_t date;
    std::vector<bot::PhotoSize> photo;
};

}

#endif //__ALICE_BOT_MESSAGE_H__
