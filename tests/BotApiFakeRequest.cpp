#include "BotApiFakeRequest.h"

bot::fakeapi::Request::Request(const std::string& token)
    : bot::api::Request(token)
{
}

bot::fakeapi::Request::Request(const bot::api::Request& other)
    : bot::api::Request(other)
{
}

CURL *
bot::fakeapi::Request::getCurl() const
{
    return this->curl;
}

bot::fakeapi::Request&
bot::fakeapi::Request::operator=(const bot::api::Request& other)
{
    bot::api::Request::operator=(other);
    return *this;
}
