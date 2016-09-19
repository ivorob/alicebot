#ifndef __ALICE_BOT_TYPE_CHAT_H__
#define __ALICE_BOT_TYPE_CHAT_H__

#include <stdint.h>
#include <json/json.h>
#include <string>
#include "types/User.h"

namespace bot {

class Chat : public User {
public:
    Chat();
    Chat(int64_t id,
         const std::string& type,
         const std::string& firstName = std::string(),
         const std::string& lastName = std::string(),
         const std::string& login = std::string(),
         const std::string& title = std::string());
    Chat(const Json::Value& chat);

    virtual const std::string& getType() const;
    virtual const std::string& getTitle() const;
protected:
    void fetchData(const Json::Value& chat);

    std::string fetchType(const Json::Value& chat) const;
    std::string fetchTitle(const Json::Value& chat) const;
private:
    std::string type;
    std::string title;
};

}

#endif //__ALICE_BOT_TYPE_CHAT_H__
