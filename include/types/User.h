#ifndef __ALICE_BOT_USER_H__
#define __ALICE_BOT_USER_H__

#include <stdint.h>
#include <string>
#include <json/json.h>

namespace bot {

class User {
public:
    User();
    User(int64_t userId,
        const std::string& firstName = std::string(),
        const std::string& lastName = std::string(),
        const std::string& username = std::string());
    User(const Json::Value& user);

    virtual int64_t getId() const;

    virtual const std::string& getFirstName() const;
    virtual const std::string& getLastName() const;
    virtual const std::string& getLogin() const;

    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
private:
    void fetchData(const Json::Value& user);

    int64_t fetchUserId(const Json::Value& user) const;
    std::string fetchFirstName(const Json::Value& user) const;
    std::string fetchLastName(const Json::Value& user) const;
    std::string fetchLogin(const Json::Value& user) const;
private:
    int64_t userId;
    std::string firstName;
    std::string lastName;
    std::string username;
};

}

#endif //__ALICE_BOT_USER_H__
