#ifndef __ALICE_BOT_USER_TEST_H__
#define __ALICE_BOT_USER_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class UserTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UserTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testCompare);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
    void testCompare();
};

#endif //__ALICE_BOT_USER_TEST_H__
