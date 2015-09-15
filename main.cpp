#include <iostream>
#include <curl/curl.h>

#define BOT_TOKEN   "124206091:AAG-WjIsE6i4jC91qsQCmtcG69sli5mARh4"
#define API_URL     "https://api.telegram.org/bot" BOT_TOKEN "/"

size_t
write_to_string(void *ptr, size_t size, size_t count, void *stream)
{
    ((std::string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}

int
main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL "getUpdates");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");

        CURLcode result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed " <<
                curl_easy_strerror(result) << std::endl;
        } else {
            std::cout << "RESPONSE: " << std::endl <<
                response << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
