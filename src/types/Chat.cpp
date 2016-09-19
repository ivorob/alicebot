#include "types/Chat.h"

bot::Chat::Chat()
{
}

bot::Chat::Chat(int64_t id, 
    const std::string& type,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& login,
    const std::string& title)
    : User(id, firstName, lastName, login),
      type(type),
      title(title)
{
}

bot::Chat::Chat(const Json::Value& chat)
    : User(chat)
{
    fetchData(chat);
}

void
bot::Chat::fetchData(const Json::Value& chat)
{
    if (chat.isObject()) {
        this->type = fetchType(chat);
        this->title = fetchTitle(chat);
    }
}

std::string
bot::Chat::fetchType(const Json::Value& chat) const
{
    Json::Value type = chat.get("type", "");
    if (type.isString()) {
        return type.asString();
    }

    return "";
}

std::string
bot::Chat::fetchTitle(const Json::Value& chat) const
{
    Json::Value title = chat.get("title", "");
    if (title.isString()) {
        return title.asString();
    }

    return "";
}

const std::string&
bot::Chat::getType() const
{
    return this->type;
}

const std::string&
bot::Chat::getTitle() const
{
    return this->title;
}
