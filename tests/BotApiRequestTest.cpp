#include <gtest/gtest.h>
#include "BotApiFakeRequest.h"

TEST(BotApiRequestTest, create)
{
    bot::fakeapi::Request request("accesstoken");
    ASSERT_TRUE(request.getToken() == "accesstoken");
}

TEST(BotApiRequestTest, copy)
{
    bot::fakeapi::Request request("accesstoken");
    bot::fakeapi::Request request1 = request;
    ASSERT_TRUE(request.getToken() == request1.getToken());

    bot::fakeapi::Request request2("newaccesstoken");
    request1 = request2;
    ASSERT_TRUE(request1.getToken() == request2.getToken());
}
