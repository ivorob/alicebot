#ifndef __ALICE_BOT_USER_H__
#define __ALICE_BOT_USER_H__

#include <string>
#include <json/json.h>

namespace bot {

class User {
public:
    User();
    User(int userId,
        const std::string& firstName = std::string(),
        const std::string& lastName = std::string(),
        const std::string& username = std::string());
    User(const Json::Value& user);

    int getId() const;

    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getLogin() const;

    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
private:
    void fetchData(const Json::Value& user);

    int fetchUserId(const Json::Value& user);
    std::string fetchFirstName(const Json::Value& user) const;
    std::string fetchLastName(const Json::Value& user) const;
    std::string fetchLogin(const Json::Value& user) const;
private:
    int userId;
    std::string firstName;
    std::string lastName;
    std::string username;
};

}

#endif //__ALICE_BOT_USER_H__
