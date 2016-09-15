#include "types/User.h"

bot::User::User()
    : userId(0)
{
}

bot::User::User(int userId, const std::string& firstName, const std::string& lastName, const std::string& username)
    : userId(userId),
      firstName(firstName),
      lastName(lastName),
      username(username)
{
}

bot::User::User(const Json::Value& user)
    : userId(0)
{
    fetchData(user);
}

void
bot::User::fetchData(const Json::Value& user)
{
    if (user.isObject()) {
        this->userId = fetchUserId(user);
        this->firstName = fetchFirstName(user);
        this->lastName = fetchLastName(user);
        this->username = fetchLogin(user);
    }
}

int
bot::User::fetchUserId(const Json::Value& user)
{
    int defaultValue = 0;

    Json::Value userId = user.get("id", defaultValue);
    if (userId.isNumeric()) {
        return userId.asInt();
    }

    return defaultValue;
}

std::string
bot::User::fetchFirstName(const Json::Value& user) const
{
    const char *defaultValue = "";

    Json::Value firstName = user.get("first_name", defaultValue);
    if (firstName.isString()) {
        return firstName.asString();
    }

    return defaultValue;
}

std::string
bot::User::fetchLastName(const Json::Value& user) const
{
    const char *defaultValue = "";

    Json::Value lastName = user.get("last_name", defaultValue);
    if (lastName.isString()) {
        return lastName.asString();
    }

    return defaultValue;
}

std::string
bot::User::fetchLogin(const Json::Value& user) const
{
    Json::Value username = user.get("username", std::string()); 
    if (username.isString()) {
        return username.asString();
    }

    return std::string();
}

int
bot::User::getId() const
{
    return this->userId;
}

const std::string&
bot::User::getFirstName() const
{
    return this->firstName;
}

const std::string&
bot::User::getLastName() const
{
    return this->lastName;
}

const std::string&
bot::User::getLogin() const
{
    return this->username;
}

bool
bot::User::operator==(const bot::User& other) const
{
    if (getId() == other.getId()) {
        return true;
    }

    return false;
}

bool
bot::User::operator!=(const bot::User& other) const
{
    return !operator==(other);
}
