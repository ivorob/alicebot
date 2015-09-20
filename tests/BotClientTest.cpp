#include <memory>
#include "BotClientTest.h"
#include "BotApiFakeRequest.h"
#include "BotMessageObserver.h"
#include "BotClient.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BotClientTest);

namespace {

class TestObserver : public bot::MessageObserver {
public:
    TestObserver() = default;

    TestObserver(const std::string& name) 
        : bot::MessageObserver(name)
    {
    }

    virtual void handleMessage(bot::Client& client) {
        const bot::Message& message = client.getLastMessage();
        text = message.getText();
    }

    const std::string& getText() const {
        return this->text;
    }
private:
    std::string text;
};

}

void
BotClientTest::setUp()
{
}

void
BotClientTest::tearDown()
{
}

void
BotClientTest::testCreate()
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    CPPUNIT_ASSERT(!client.hasObservers());
}

void
BotClientTest::testRegisterObserver()
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    CPPUNIT_ASSERT(!client.hasObservers());

    client.registerObserver(nullptr);
    CPPUNIT_ASSERT(!client.hasObservers());

    client.registerObserver(new TestObserver);
    CPPUNIT_ASSERT(client.hasObservers());
}

void
BotClientTest::testRemoveObserver()
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    CPPUNIT_ASSERT(!client.hasObservers());

    client.registerObserver(new TestObserver("Logger"));
    CPPUNIT_ASSERT(client.hasObservers());
    client.removeObserver("WrongName");
    CPPUNIT_ASSERT(client.hasObservers());
    client.removeObserver("Logger");
    CPPUNIT_ASSERT(!client.hasObservers());
}

void
BotClientTest::testNotification()
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    CPPUNIT_ASSERT(!client.hasObservers());

    TestObserver *observer = new TestObserver("Logger");
    client.registerObserver(observer);
    CPPUNIT_ASSERT(client.hasObservers());

    CPPUNIT_ASSERT(observer->getText().empty());
    client.processOnce();
    CPPUNIT_ASSERT_EQUAL(std::string("How are you?"), observer->getText());
}
