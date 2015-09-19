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

    Request& operator=(const bot::api::Request& other);
};

}

}

#endif //__ALICE_BOT_API_FAKE_REQUEST_H__
