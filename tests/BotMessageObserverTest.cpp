#include <gtest/gtest.h>
#include "BotMessageObserver.h"

namespace {

class TestObserver : public bot::MessageObserver {
public:
    TestObserver(const std::string& name)
        : bot::MessageObserver(name)
    {
    }

    virtual void handleMessage(bot::Client& client) {
    }
};

}

TEST(BotMessageObserver, name)
{
    TestObserver observer("Logger");
    ASSERT_EQ(std::string("Logger"), observer.getName());
}
