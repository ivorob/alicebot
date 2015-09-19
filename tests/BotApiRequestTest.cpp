#include "BotApiRequestTest.h"
#include "BotApiFakeRequest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BotApiRequestTest);

void
BotApiRequestTest::setUp()
{
}

void
BotApiRequestTest::tearDown()
{
}

void
BotApiRequestTest::testCreate()
{
    bot::fakeapi::Request request("accesstoken");
    CPPUNIT_ASSERT(request.getToken() == "accesstoken");
}

void
BotApiRequestTest::testCopy()
{
    bot::fakeapi::Request request("accesstoken");
    bot::fakeapi::Request request1 = request;
    CPPUNIT_ASSERT(request.getToken() == request1.getToken());
    CPPUNIT_ASSERT(request.getCurl() != request1.getCurl());

    bot::fakeapi::Request request2("newaccesstoken");
    request1 = request2;
    CPPUNIT_ASSERT(request1.getToken() == request2.getToken());
    CPPUNIT_ASSERT(request1.getCurl() != request2.getCurl() &&
                   request1.getCurl() != request.getCurl() &&
                   request2.getCurl() != request.getCurl());
}
