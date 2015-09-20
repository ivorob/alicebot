#ifndef __ALICE_BOT_CLIENT_TEST_H__
#define __ALICE_BOT_CLIENT_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class BotClientTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BotClientTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testRegisterObserver);
    CPPUNIT_TEST(testRemoveObserver);
    CPPUNIT_TEST(testNotification);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
    void testRegisterObserver();
    void testRemoveObserver();
    void testNotification();
};

#endif //__ALICE_BOT_CLIENT_TEST_H__
