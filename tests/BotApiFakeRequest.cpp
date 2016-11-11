#include "BotApiFakeRequest.h"

bot::fakeapi::Request::Request(const std::string& token)
    : bot::api::Request(token)
{
}

bot::fakeapi::Request::Request(const bot::api::Request& other)
    : bot::api::Request(other)
{
}

bot::fakeapi::Request&
bot::fakeapi::Request::operator=(const bot::api::Request& other)
{
    bot::api::Request::operator=(other);
    return *this;
}

std::string
bot::fakeapi::Request::perform(const std::string& method, bot::api::RequestList list)
{
    std::string result;
    if (method == "getUpdates") {
        result = "{\"ok\":true,\"result\":[{\"update_id\":102,"
                 "\"message\":{\"message_id\":4,\"from\":{\"id\":123456,"
                 "\"first_name\":\"Test\",\"last_name\":\"User\"},"
                 "\"chat\":{\"id\":123456,\"first_name\":\"Test\","
                 "\"last_name\":\"User\"},\"date\":1442358956,"
                 "\"text\":\"How are you?\"}}]}";
    } else if (method == "getMe") {
        result = "{\"ok\":true,\"result\":{\"id\":124206091,\"first_name\":\"Alice\",\"username\":\"TestAliceBot\"}}";
    } else if (method == "getChat") {
        result = "{\"ok\":true,\"result\":{\"id\":83132472,\"first_name\":\"Test\",\"last_name\":\"User\",\"username\":\"testuser\",\"type\":\"private\",\"title\":\"sometitle\"}}";
    }

    return result;
}
