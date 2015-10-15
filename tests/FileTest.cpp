#include <jsoncpp/json/json.h>
#include "FileTest.h"
#include "types/File.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FileTest);

void
FileTest::setUp()
{
}

void
FileTest::tearDown()
{
}

void
FileTest::testCreate()
{
    Json::Value root;
    Json::Reader reader;

    CPPUNIT_ASSERT(reader.parse("{\"file_id\":\"AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABK29uSrxfo--o8YAAgI\",\"file_size\":22498,\"file_path\":\"photo\\/file_1.jpg\"}", root));

    bot::File file(root);
    CPPUNIT_ASSERT(file.getId() == "AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABK29uSrxfo--o8YAAgI");
    CPPUNIT_ASSERT(file.getSize() == 22498);
    CPPUNIT_ASSERT(file.getPath() == "photo/file_1.jpg");
}
