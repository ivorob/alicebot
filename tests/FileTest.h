#ifndef __ALICE_BOT_FILE_TEST_H__
#define __ALICE_BOT_FILE_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class FileTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(FileTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
};

#endif //__ALICE_BOT_FILE_TEST_H__
