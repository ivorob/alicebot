#include <gtest/gtest.h>
#include <jsoncpp/json/json.h>
#include "types/Message.h"

TEST(MessageTest, create)
{
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("{\"message_id\":1,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442455683,\"text\":\"How are you?\"}", root));

    bot::Message message(root);
    ASSERT_TRUE(message.getId() == 1);
    ASSERT_TRUE(message.getFrom() == bot::User(123456, "Test", "User"));
    ASSERT_TRUE(message.getText() == "How are you?");

    ASSERT_TRUE(reader.parse("{\"message_id\":2,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442456125,\"text\":\"\\u041a\\u0430\\u043a \\u0442\\u0432\\u043e\\u0438 \\u0434\\u0435\\u043b\\u0430?\"}", root));
    bot::Message message1(root);
    ASSERT_TRUE(message1.getId() == 2);
    ASSERT_TRUE(message1.getText() == "Как твои дела?");

    bot::Message message2;
    ASSERT_TRUE(message2.getId() == 0);
    ASSERT_TRUE(message2.getText().empty());
}

TEST(MessageTest, testDate)
{
    Json::Value root;
    Json::Reader reader;

    ASSERT_TRUE(reader.parse("{\"message_id\":1,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442455683,\"text\":\"How are you?\"}", root));

    bot::Message message(root);
    time_t date = message.getDate();
    ASSERT_TRUE(static_cast<long int>(date) == 1442455683);
}

TEST(MessageTest, hasAttachments)
{
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("{\"message_id\":260,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\",\"type\":\"private\"},\"date\":1444864416,\"photo\":[{\"file_id\":\"AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABIFzITadRgAB36XGAAIC\",\"file_size\":1851,\"width\":85,\"height\":90},{\"file_id\":\"AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABB6bUfXRmslLpMYAAgI\",\"file_size\":19719,\"width\":303,\"height\":320},{\"file_id\":\"AgADAgADrKcxGzyA9AQsk9BigTA_s0BGhCoABK29uSrxfo--o8YAAgI\",\"file_size\":22498,\"width\":379,\"height\":400}]}", root));

    bot::Message message(root);
    ASSERT_TRUE(message.hasAttachments());

    ASSERT_TRUE(reader.parse("{\"message_id\":1,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442455683,\"text\":\"How are you?\"}", root));
    bot::Message message1(root);
    ASSERT_TRUE(!message1.hasAttachments());
}
