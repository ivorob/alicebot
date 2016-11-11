#include <thread>
#include "CurlRequest.h"

namespace {

size_t
write_to_string(void *data, size_t size, size_t count, void *stream)
{
    ((std::string *)stream)->append((char *)data, size * count);
    return size * count;
}

}

CURLWrapper::Request::Request(const std::string& url, int waitInterval)
    : multiHandle(0),
      waitInterval(waitInterval)
{
    this->curl = curl_easy_init();
    if (!this->curl) {
        throw std::runtime_error("Can not initialize curl");
    }

    this->multiHandle = curl_multi_init();
    if (!this->multiHandle) {
        throw std::runtime_error("Can not initialize curl multi handle");
    }

    curl_easy_setopt(this->curl, CURLOPT_HEADER, false);
    curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(this->curl, CURLOPT_SSL_VERIFYHOST, 0L);

    setUrl(url);
}

CURLWrapper::Request::~Request()
{
    curl_multi_cleanup(this->multiHandle);
    curl_easy_cleanup(this->curl);
}

void
CURLWrapper::Request::addFileField(const std::string& name, const std::string& filename)
{
    this->files[name] = filename;
}

std::string
CURLWrapper::Request::perform(const std::string& url, std::initializer_list<value_type> list) 
{
    setUrl(url);

    std::string response;
    if (this->files.empty() && list.size() == 0) {
        response = performGetRequest();
    } else {
        response = performPostRequest(list);
    }

    return response;
}

std::string
CURLWrapper::Request::performPostRequest(std::initializer_list<value_type> list)
{
    curl_multi_add_handle(this->multiHandle, this->curl);

    struct curl_slist *headerlist = 0;
    headerlist = curl_slist_append(headerlist, "Expect:");
    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, headerlist);

    std::string response;
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);

    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    for (const auto& param : list) {
        curl_formadd(&formpost,
            &lastptr,
            CURLFORM_COPYNAME, param.first.c_str(),
            CURLFORM_COPYCONTENTS, param.second.c_str(),
            CURLFORM_END);
    }

    for (const auto& file: this->files) {
        const std::string& fieldName = file.first;
        const std::string& filename = file.second;

        curl_formadd(&formpost,
                &lastptr,
                CURLFORM_COPYNAME, fieldName.c_str(),
                CURLFORM_FILE, filename.c_str(),
                CURLFORM_END);
    }

    curl_easy_setopt(this->curl, CURLOPT_HTTPPOST, formpost);

    int still_running = 0;
    do {
        curl_multi_perform(this->multiHandle, &still_running);
        std::this_thread::sleep_for(std::chrono::milliseconds(this->waitInterval));
    } while (still_running);

    curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, 0);
    curl_easy_setopt(this->curl, CURLOPT_HTTPPOST, 0);

    curl_formfree(formpost);
    curl_slist_free_all(headerlist);
    curl_multi_remove_handle(this->multiHandle, this->curl);
    handleResponseCode();

    return response;
}

std::string
CURLWrapper::Request::performGetRequest()
{
    std::string response;
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(this->curl, CURLOPT_POST, false);

    CURLcode result = curl_easy_perform(this->curl);
    if (result != CURLE_OK) {
        throw std::runtime_error("Can not perform curl request");
    }

    handleResponseCode();
    return response;
}

void
CURLWrapper::Request::handleResponseCode()
{
    long responseCode = 200;
    curl_easy_getinfo(this->curl, CURLINFO_RESPONSE_CODE, &responseCode);
    if (responseCode == 0) {
        throw std::runtime_error("Can not get response from server");
    } else if (responseCode >= 400 && responseCode < 600) {
        throw std::runtime_error("Response code: " + std::to_string(responseCode));
    }
}

void
CURLWrapper::Request::resetFormData()
{
    this->files.clear();
}

void
CURLWrapper::Request::setUrl(const std::string& url)
{
    if (!url.empty()) {
        curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    }
}

std::string
CURLWrapper::Request::urlencode(const std::string& text)
{
    std::string result;

    if (!text.empty()) {
        char *encoded = curl_easy_escape(this->curl, text.c_str(), text.size());
        if (encoded != 0) {
            result = encoded;
            curl_free(encoded);
        }
    }

    return result;
}
