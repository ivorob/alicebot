#include "BotMessageObserverTest.h"
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

CPPUNIT_TEST_SUITE_REGISTRATION(BotMessageObserverTest);

void
BotMessageObserverTest::setUp()
{
}

void
BotMessageObserverTest::tearDown()
{
}

void
BotMessageObserverTest::testName()
{
    TestObserver observer("Logger");
    CPPUNIT_ASSERT_EQUAL(std::string("Logger"), observer.getName());
}
