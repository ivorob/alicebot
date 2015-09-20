#ifndef __ALICE_BOT_API_FAKE_REQUEST_H__
#define __ALICE_BOT_API_FAKE_REQUEST_H__

#include "BotApiRequest.h"

namespace bot {

namespace fakeapi {

class Request : public bot::api::Request {
public:
    Request() = delete;
    Request(const std::string& token);
    Request(const bot::api::Request& other);

    CURL *getCurl() const;

    virtual std::string perform(const std::string& method,
        const std::string& data);

    Request& operator=(const bot::api::Request& other);
};

}

}

#endif //__ALICE_BOT_API_FAKE_REQUEST_H__
