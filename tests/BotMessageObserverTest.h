#ifndef __ALICE_BOT_MESSAGE_OBSERVER_TEST_H__
#define __ALICE_BOT_MESSAGE_OBSERVER_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class BotMessageObserverTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BotMessageObserverTest);
    CPPUNIT_TEST(testName);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testName();
};

#endif //__ALICE_BOT_MESSAGE_OBSERVER_TEST_H__
