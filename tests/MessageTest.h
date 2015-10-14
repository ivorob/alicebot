#ifndef __ALICE_BOT_MESSAGE_TEST_H__
#define __ALICE_BOT_MESSAGE_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class MessageTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MessageTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testDate);
    CPPUNIT_TEST(testHasAttachments);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
    void testDate();
    void testHasAttachments();
};

#endif //__ALICE_BOT_MESSAGE_TEST_H__
