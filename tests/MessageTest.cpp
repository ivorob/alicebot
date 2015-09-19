#include <jsoncpp/json/json.h>
#include "MessageTest.h"
#include "Message.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MessageTest);

void
MessageTest::setUp()
{
}

void
MessageTest::tearDown()
{
}

void
MessageTest::testCreate()
{
    Json::Value root;
    Json::Reader reader;
    CPPUNIT_ASSERT(reader.parse("{\"message_id\":1,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442455683,\"text\":\"How are you?\"}", root));

    bot::Message message(root);
    CPPUNIT_ASSERT(message.getId() == 1);
    CPPUNIT_ASSERT(message.getFrom() == bot::User(123456, "Test", "User"));
    CPPUNIT_ASSERT(message.getText() == "How are you?");

    CPPUNIT_ASSERT(reader.parse("{\"message_id\":2,\"from\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"chat\":{\"id\":123456,\"first_name\":\"Test\",\"last_name\":\"User\"},\"date\":1442456125,\"text\":\"\\u041a\\u0430\\u043a \\u0442\\u0432\\u043e\\u0438 \\u0434\\u0435\\u043b\\u0430?\"}", root));
    bot::Message message1(root);
    CPPUNIT_ASSERT(message1.getId() == 2);
    CPPUNIT_ASSERT(message1.getText() == "Как твои дела?");
}
