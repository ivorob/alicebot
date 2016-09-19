#include <gtest/gtest.h>
#include <json/json.h>
#include "types/Chat.h"

TEST(ChatTest, create)
{
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("{\"id\":83132472,\"first_name\":\"Test\",\"last_name\":\"User\",\"username\":\"testuser\",\"type\":\"private\",\"title\":\"sometitle\"}", root));

    bot::Chat chat(root);
    ASSERT_EQ(83132472, chat.getId());
    ASSERT_EQ("Test", chat.getFirstName());
    ASSERT_EQ("User", chat.getLastName());
    ASSERT_EQ("testuser", chat.getLogin());
    ASSERT_EQ("private", chat.getType());
    ASSERT_EQ("sometitle", chat.getTitle());

    bot::Chat chat1(1, "private", "Test", "User", "testuser", "sometitle");
    ASSERT_EQ(1, chat1.getId());
    ASSERT_EQ("private", chat1.getType());
    ASSERT_EQ("Test", chat1.getFirstName());
    ASSERT_EQ("User", chat1.getLastName());
    ASSERT_EQ("testuser", chat1.getLogin());
    ASSERT_EQ("sometitle", chat1.getTitle());
}
