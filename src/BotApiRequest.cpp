#include <curl/curl.h>
#include "BotApiRequest.h"

namespace {

size_t
write_to_string(void *data, size_t size, size_t count, void *stream)
{
    ((std::string *)stream)->append((char *)data, 0, size * count);
    return size * count;
}

}

bot::api::Request::Request(const std::string& token)
    : token(token)
{
    this->curl = curl_easy_init();
    if (!this->curl) {
        //TODO generate exception
    }
}

bot::api::Request::Request(const Request& other)
    : token(other.token)
{
    this->curl = curl_easy_init();
    if (!this->curl) {
        //TODO: generate exception
    }
}

std::string
bot::api::Request::perform(const std::string& method, const std::string& data)
{
    std::string url = "https://api.telegram.org/bot" + this->token + "/" + method;
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYHOST, 0L);

    std::string response;
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);

    if (!data.empty()) {
        curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, data.c_str());
    }

    CURLcode result = curl_easy_perform(this->curl);
    if (result != CURLE_OK) {
        //TODO: exception
    }

    return response;
}

bot::api::Request::~Request()
{
    curl_easy_cleanup(this->curl);
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
    std::string result;

    if (!text.empty()) {
        char *encoded = curl_easy_escape(curl, text.c_str(), text.size());
        if (encoded != 0) {
            result = encoded;
            curl_free(encoded);
        }
    }

    return result;
}
