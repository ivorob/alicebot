#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>
#include "types/PhotoSize.h"

TEST(PhotoSize, create)
{
    bot::PhotoSize photoSize;
    ASSERT_TRUE(photoSize.getId().empty());
    ASSERT_TRUE(photoSize.getWidth() == 0);
    ASSERT_TRUE(photoSize.getHeight() == 0);
    ASSERT_TRUE(photoSize.getSize() == 0);

    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("[{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABE_gOSsN14mZg7gBAAEC\",\"file_size\":1855,\"width\":85,\"height\":90},{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABHuI0gwCPqgcgrgBAAEC\",\"file_size\":19321,\"width\":303,\"height\":320},{\"file_id\":\"AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABJ2pkTPNX_sSgbgBAAEC\",\"file_size\":20239,\"width\":379,\"height\":400}]", root));
    ASSERT_TRUE(root.size() == 3);
    
    bot::PhotoSize photoSize1(root[0]);
    ASSERT_TRUE(photoSize1.getId() == "AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABE_gOSsN14mZg7gBAAEC");
    ASSERT_TRUE(photoSize1.getWidth() == 85);
    ASSERT_TRUE(photoSize1.getHeight() == 90);
    ASSERT_TRUE(photoSize1.getSize() == 1855);
    
    bot::PhotoSize photoSize2(root[2]);
    ASSERT_TRUE(photoSize2.getId() == "AgADAgADq6cxGzyA9ASDVaV95duBkQLjWSoABJ2pkTPNX_sSgbgBAAEC");
    ASSERT_TRUE(photoSize2.getWidth() == 379);
    ASSERT_TRUE(photoSize2.getHeight() == 400);
    ASSERT_TRUE(photoSize2.getSize() == 20239);
}
