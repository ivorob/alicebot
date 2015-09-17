#ifndef __BOT_API_REQUEST_H__
#define __BOT_API_REQUEST_H__

#include <string>
#include <curl/curl.h>

namespace bot {

namespace api {

class Request {
public:
    Request() = delete;
    Request(const std::string& token);
    ~Request();

    std::string perform(const std::string& method, const std::string& data = std::string());
private:
    std::string token;
    CURL *curl;
};

}

}

#endif //__BOT_API_REQUEST_H__
