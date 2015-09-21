#ifndef __ALICE_BOT_PHOTO_SIZE_TEST_H__
#define __ALICE_BOT_PHOTO_SIZE_TEST_H__

#include <cppunit/extensions/HelperMacros.h>

class PhotoSizeTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(PhotoSizeTest);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testCreate();
};

#endif //__ALICE_BOT_PHOTO_SIZE_TEST_H__
