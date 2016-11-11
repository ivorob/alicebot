#ifndef __CURL_WRAPPER_REQUEST_H__
#define __CURL_WRAPPER_REQUEST_H__

#include <curl/curl.h>
#include <string>
#include <map>
#include <stdarg.h>

namespace CURLWrapper {

class Request {
public:
    typedef std::pair<std::string,std::string> value_type;
public:
    Request(const std::string& url = std::string(), int waitInterval = 10);
    ~Request();

    void addFileField(const std::string& name, const std::string& filename);

    std::string perform(const std::string& url, std::initializer_list<value_type> list = std::initializer_list<value_type>()); 
    std::string urlencode(const std::string& url);

    void resetFormData();
    void setUrl(const std::string& url);
private:
    std::string performPostRequest(std::initializer_list<value_type> list);
    std::string performGetRequest();
private:
    void handleResponseCode();
private:
    CURL *curl;
    CURLM *multiHandle;
    std::map<std::string,std::string> files;
    int waitInterval;
};

}

#endif //__CURL_WRAPPER_REQUEST_H__
