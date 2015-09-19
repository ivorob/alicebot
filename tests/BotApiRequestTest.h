#ifndef __ALICE_BOT_API_REQUEST_TEST_H__
#define __ALICE_BOT_API_REQUEST_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class BotApiRequestTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BotApiRequestTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testCopy);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
    void testCopy();
};

#endif //__ALICE_BOT_API_REQUEST_TEST_H__
