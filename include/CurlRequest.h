#ifndef __CURL_WRAPPER_REQUEST_H__
#define __CURL_WRAPPER_REQUEST_H__

#include <curl/curl.h>
#include <string>
#include <map>
#include <stdarg.h>

namespace CURLWrapper {

class Request {
public:
    Request(const std::string& url = std::string(), int waitInterval = 10);
    ~Request();

    void addFileField(const std::string& name, const std::string& filename);

    std::string perform(const std::string& url, int params, va_list list); 
    std::string perform(const std::string& url = std::string(), int params = 0, ...);
    std::string urlencode(const std::string& url);

    void resetFormData();
    void setUrl(const std::string& url);
private:
    std::string performPostRequest(int params, va_list list);
    std::string performGetRequest();
private:
    void fillPostForm(struct curl_httppost **first, struct curl_httppost **last, int params, va_list list);
    void handleResponseCode();
private:
    CURL *curl;
    CURLM *multiHandle;
    std::map<std::string,std::string> files;
    int waitInterval;
};

}

#endif //__CURL_WRAPPER_REQUEST_H__
