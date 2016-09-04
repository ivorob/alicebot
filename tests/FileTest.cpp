#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>
#include "types/File.h"

TEST(FileTest, create)
{
    Json::Value root;
    Json::Reader reader;

    ASSERT_TRUE(reader.parse("{\"file_id\":\"AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABK29uSrxfo--o8YAAgI\",\"file_size\":22498,\"file_path\":\"photo\\/file_1.jpg\"}", root));

    bot::File file(root);
    ASSERT_TRUE(file.getId() == "AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABK29uSrxfo--o8YAAgI");
    ASSERT_TRUE(file.getSize() == 22498);
    ASSERT_TRUE(file.getPath() == "photo/file_1.jpg");

    bot::File file1;
    ASSERT_TRUE(file1.getId() == "");
    ASSERT_TRUE(file1.getSize() == 0);
    ASSERT_TRUE(file1.getPath() == "");
}
