#include <gtest/gtest.h>
#include <memory>
#include "BotApiFakeRequest.h"
#include "BotMessageObserver.h"
#include "BotClient.h"

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

TEST(BotClientTest, create)
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    ASSERT_TRUE(!client.hasObservers());
}

TEST(BotClientTest, registerObserver)
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    ASSERT_TRUE(!client.hasObservers());

    client.registerObserver(nullptr);
    ASSERT_TRUE(!client.hasObservers());

    client.registerObserver(new TestObserver);
    ASSERT_TRUE(client.hasObservers());
}

TEST(BotClientTest, removeObserver)
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    ASSERT_TRUE(!client.hasObservers());

    client.registerObserver(new TestObserver("Logger"));
    ASSERT_TRUE(client.hasObservers());
    client.removeObserver("WrongName");
    ASSERT_TRUE(client.hasObservers());
    client.removeObserver("Logger");
    ASSERT_TRUE(!client.hasObservers());
}

TEST(BotClientTest, notification)
{
    std::unique_ptr<bot::fakeapi::Request> request(new bot::fakeapi::Request("accesstoken"));
    bot::Client client(request.get());
    ASSERT_TRUE(!client.hasObservers());

    TestObserver *observer = new TestObserver("Logger");
    client.registerObserver(observer);
    ASSERT_TRUE(client.hasObservers());

    ASSERT_TRUE(observer->getText().empty());
    client.processOnce();
    ASSERT_EQ("How are you?", observer->getText());
}
