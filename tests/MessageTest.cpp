#include <gtest/gtest.h>
#include <json/json.h>
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

TEST(MessageTest, getPhoto)
{
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("{\"message_id\":285,\"from\":{\"id\":83132476,\"first_name\":\"Ivan\",\"last_name\":\"Vorobyev\",\"username\":\"pusir\"},\"chat\":{\"id\":83132476,\"first_name\":\"Ivan\",\"last_name\":\"Vorobyev\",\"username\":\"pusir\",\"type\":\"private\"},\"date\":1473808506,\"photo\":[{\"file_id\":\"AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABNFxXLdHE1HMY-sBAAEC\",\"file_size\":1137,\"width\":90,\"height\":67},{\"file_id\":\"AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABNwdZiKz6gXgZOsBAAEC\",\"file_size\":15485,\"width\":320,\"height\":240},{\"file_id\":\"AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABLy45sOf8MjHZesBAAEC\",\"file_size\":70722,\"width\":800,\"height\":600},{\"file_id\":\"AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABAQQSQR7nUvLYusBAAEC\",\"file_size\":121233,\"width\":1280,\"height\":960}]}", root));

    bot::Message message(root);
    ASSERT_TRUE(message.hasAttachments());

    const bot::Message::Photo photo = message.getPhoto();
    bot::Message::Photo::const_iterator currentPhoto = photo.begin();
    ASSERT_EQ("AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABNFxXLdHE1HMY-sBAAEC", currentPhoto->getId());
    ASSERT_EQ(1137, currentPhoto->getSize());
    ASSERT_EQ(90, currentPhoto->getWidth());
    ASSERT_EQ(67, currentPhoto->getHeight());

    currentPhoto++;
    ASSERT_EQ("AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABNwdZiKz6gXgZOsBAAEC", currentPhoto->getId());
    ASSERT_EQ(15485, currentPhoto->getSize());
    ASSERT_EQ(320, currentPhoto->getWidth());
    ASSERT_EQ(240, currentPhoto->getHeight());

    currentPhoto++;
    ASSERT_EQ("AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABLy45sOf8MjHZesBAAEC", currentPhoto->getId());
    ASSERT_EQ(70722, currentPhoto->getSize());
    ASSERT_EQ(800, currentPhoto->getWidth());
    ASSERT_EQ(600, currentPhoto->getHeight());

    currentPhoto++;
    ASSERT_EQ("AgADAgADracxGzyA9ARawzSmHIHCZbsUcQ0ABAQQSQR7nUvLYusBAAEC", currentPhoto->getId());
    ASSERT_EQ(121233, currentPhoto->getSize());
    ASSERT_EQ(1280, currentPhoto->getWidth());
    ASSERT_EQ(960, currentPhoto->getHeight());

    currentPhoto++;
    ASSERT_EQ(photo.end(), currentPhoto);
}
