#ifndef __BOT_API_REQUEST_H__
#define __BOT_API_REQUEST_H__

#include <string>
#include <curl/curl.h>
#include "CurlRequest.h"
#include "types/User.h"

namespace bot {

namespace api {

class Request {
public:
    typedef std::pair<std::string,std::string> value_type;
public:
    Request() = delete;
    Request(const std::string& token);
    Request(const Request& other);
    virtual ~Request();

    virtual std::string sendFile(const bot::User& user, const std::string& path, const std::string& method, const std::string& filename);
    virtual std::string perform(const std::string& method, std::initializer_list<value_type> list = std::initializer_list<value_type>());
    virtual std::string downloadFile(const std::string& path);

    const std::string& getToken() const;

    Request& operator=(const Request& other);

    std::string urlencode(const std::string& text);
private:
    std::string performUrl(const std::string& url, const std::string& data = std::string());
protected:
    CURLWrapper::Request request;
private:
    std::string token;
};

typedef std::initializer_list<bot::api::Request::value_type> RequestList;

}

}

#endif //__BOT_API_REQUEST_H__
