#include <jsoncpp/json/json.h>
#include "UserTest.h"
#include "types/User.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UserTest);

void
UserTest::setUp()
{
}

void
UserTest::tearDown()
{
}

void
UserTest::testCreate()
{
    Json::Value root;
    Json::Reader reader;
    CPPUNIT_ASSERT(reader.parse("{\"id\":3294738,\"first_name\":\"Test\",\"last_name\":\"User\"}", root));

    bot::User user(root);
    CPPUNIT_ASSERT(user.getId() == 3294738);
    CPPUNIT_ASSERT(user.getFirstName() == "Test");
    CPPUNIT_ASSERT(user.getLastName() == "User");

    CPPUNIT_ASSERT(reader.parse("{\"id\":29821374,\"first_name\":\"Test\",\"last_name\":\"User\"}", root));
    bot::User user1(root);
    CPPUNIT_ASSERT(user1.getId() == 29821374);

    CPPUNIT_ASSERT(reader.parse("{\"id\":\"wrong number\",\"first_name\":1234567,\"last_name\":173.23}", root));
    bot::User user2(root);
    CPPUNIT_ASSERT(user2.getId() == 0);
    CPPUNIT_ASSERT(user2.getFirstName().empty());
    CPPUNIT_ASSERT(user2.getLastName().empty());

    bot::User user3;
    CPPUNIT_ASSERT(user3.getId() == 0);
    CPPUNIT_ASSERT(user3.getFirstName().empty());
    CPPUNIT_ASSERT(user3.getLastName().empty());

    bot::User user4(1, "Test1", "User1");
    CPPUNIT_ASSERT(user4.getId() == 1);
    CPPUNIT_ASSERT(user4.getFirstName() == "Test1");
    CPPUNIT_ASSERT(user4.getLastName() == "User1");
}

void
UserTest::testCompare()
{
    bot::User user;
    CPPUNIT_ASSERT(user == bot::User());

    bot::User user1(1, "Test1", "");
    CPPUNIT_ASSERT(user1 == bot::User(1, "Test1"));
    CPPUNIT_ASSERT(user1 == bot::User(1));
    CPPUNIT_ASSERT(user1 != bot::User());
}
