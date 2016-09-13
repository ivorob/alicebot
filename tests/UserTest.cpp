#include <gtest/gtest.h>
#include <json/json.h>
#include "types/User.h"

TEST(UserTest, create)
{
    Json::Value root;
    Json::Reader reader;
    ASSERT_TRUE(reader.parse("{\"id\":3294738,\"first_name\":\"Test\",\"last_name\":\"User\"}", root));

    bot::User user(root);
    ASSERT_TRUE(user.getId() == 3294738);
    ASSERT_TRUE(user.getFirstName() == "Test");
    ASSERT_TRUE(user.getLastName() == "User");

    ASSERT_TRUE(reader.parse("{\"id\":29821374,\"first_name\":\"Test\",\"last_name\":\"User\"}", root));
    bot::User user1(root);
    ASSERT_TRUE(user1.getId() == 29821374);

    ASSERT_TRUE(reader.parse("{\"id\":\"wrong number\",\"first_name\":1234567,\"last_name\":173.23}", root));
    bot::User user2(root);
    ASSERT_TRUE(user2.getId() == 0);
    ASSERT_TRUE(user2.getFirstName().empty());
    ASSERT_TRUE(user2.getLastName().empty());

    bot::User user3;
    ASSERT_TRUE(user3.getId() == 0);
    ASSERT_TRUE(user3.getFirstName().empty());
    ASSERT_TRUE(user3.getLastName().empty());

    bot::User user4(1, "Test1", "User1");
    ASSERT_TRUE(user4.getId() == 1);
    ASSERT_TRUE(user4.getFirstName() == "Test1");
    ASSERT_TRUE(user4.getLastName() == "User1");
}

TEST(UserTest, compare)
{
    bot::User user;
    ASSERT_TRUE(user == bot::User());

    bot::User user1(1, "Test1", "");
    ASSERT_TRUE(user1 == bot::User(1, "Test1"));
    ASSERT_TRUE(user1 == bot::User(1));
    ASSERT_TRUE(user1 != bot::User());
}
