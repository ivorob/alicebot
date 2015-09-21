#include <jsoncpp/json/json.h>
#include "PhotoSizeTest.h"
#include "types/PhotoSize.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PhotoSizeTest);

void
PhotoSizeTest::setUp()
{
}

void
PhotoSizeTest::tearDown()
{
}

void
PhotoSizeTest::testCreate()
{
    bot::PhotoSize photoSize;
    CPPUNIT_ASSERT(photoSize.getId().empty());
    CPPUNIT_ASSERT(photoSize.getWidth() == 0);
    CPPUNIT_ASSERT(photoSize.getHeight() == 0);
    CPPUNIT_ASSERT(photoSize.getSize() == 0);

    Json::Value root;
    Json::Reader reader;
    CPPUNIT_ASSERT(reader.parse("[{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABE_gOSsN14mZg7gBAAEC\",\"file_size\":1855,\"width\":85,\"height\":90},{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABHuI0gwCPqgcgrgBAAEC\",\"file_size\":19321,\"width\":303,\"height\":320},{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABJ2pkTPNX_sSgbgBAAEC\",\"file_size\":20239,\"width\":379,\"height\":400}]", root));
    CPPUNIT_ASSERT(root.size() == 3);
    
    bot::PhotoSize photoSize1(root[0]);
    CPPUNIT_ASSERT(photoSize1.getId() == "AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABE_gOSsN14mZg7gBAAEC");
    CPPUNIT_ASSERT(photoSize1.getWidth() == 85);
    CPPUNIT_ASSERT(photoSize1.getHeight() == 90);
    CPPUNIT_ASSERT(photoSize1.getSize() == 1855);
    
    bot::PhotoSize photoSize2(root[2]);
    CPPUNIT_ASSERT(photoSize2.getId() == "AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABJ2pkTPNX_sSgbgBAAEC");
    CPPUNIT_ASSERT(photoSize2.getWidth() == 379);
    CPPUNIT_ASSERT(photoSize2.getHeight() == 400);
    CPPUNIT_ASSERT(photoSize2.getSize() == 20239);
}
