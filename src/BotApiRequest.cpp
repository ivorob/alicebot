#include <curl/curl.h>
#include "BotApiRequest.h"
#include "RequestParam.h"

namespace {

size_t
write_to_string(void *data, size_t size, size_t count, void *stream)
{
    ((std::string *)stream)->append((char *)data, size * count);
    return size * count;
}

}

bot::api::Request::Request(const std::string& token)
    : token(token)
{
}

bot::api::Request::Request(const Request& other)
    : token(other.token)
{
}

std::string
bot::api::Request::performUrl(const std::string& url, const std::string& data)
{
    this->request.resetFormData();
    return this->request.perform(url);
}

std::string
bot::api::Request::perform(const std::string& method, int params, ...)
{
    std::string url = "https://api.telegram.org/bot" + this->token + "/" + method;
    va_list list;
    va_start(list, params);
    this->request.resetFormData();
    std::string response = this->request.perform(url, params, list);
    va_end(list);
    return response;
}

std::string
bot::api::Request::downloadFile(const std::string& path)
{
    std::string url = "https://api.telegram.org/file/bot" + this->token + "/" + path;
    return performUrl(url);
}

std::string
bot::api::Request::sendFile(const bot::User& user, const std::string& path, const std::string& method, const std::string& filename)
{
    std::string url = "https://api.telegram.org/bot" + this->token + "/" + method;
    this->request.resetFormData();
    this->request.addFileField(filename, path);
    return this->request.perform(url, 1, 
            new HttpRequest::Param<int64_t>("chat_id", user.getId()));
}

bot::api::Request::~Request()
{
}

const std::string&
bot::api::Request::getToken() const
{
    return this->token;
}

bot::api::Request&
bot::api::Request::operator=(const Request& other)
{
    if (this != &other) {
        this->token = other.token;
    }

    return *this;
}

std::string
bot::api::Request::urlencode(const std::string& text)
{
    return this->request.urlencode(text);
}
