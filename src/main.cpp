#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <jsoncpp/json/json.h>
#include "BotApiRequest.h"
#include "BotMessageObserver.h"
#include "BotClient.h"
#include "User.h"
#include "Message.h"

#define BOT_TOKEN   "124206091:AAG-WjIsE6i4jC91qsQCmtcG69sli5mARh4"

namespace {

class MessageLogger : public bot::MessageObserver {
public:
    MessageLogger()
        : bot::MessageObserver("Logger")
    {
    }

    virtual void handleMessage(bot::Client& client) {
        const bot::Message& message = client.getLastMessage();
        const bot::User& user = message.getFrom();

        std::cout << "NEW MESSAGE:" << std::endl;

        std::cout << "From:" << std::endl;
        std::cout << "USER ID   : " << user.getId() << std::endl <<
                     "FIRST NAME: " << user.getFirstName() << std::endl <<
                     "LAST NAME : " << user.getLastName() << std::endl;

        time_t date = message.getDate();
        std::cout << "date: " << std::ctime(&date)
                  << "text: " << std::endl <<
            message.getText() << std::endl << std::endl;
    }
};

class MessageReplyer: public bot::MessageObserver {
public:
    MessageReplyer()
        : bot::MessageObserver("Replyer")
    {
    }

    virtual void handleMessage(bot::Client& client) {
        const bot::Message& message = client.getLastMessage();
        const bot::User& user = message.getFrom();
        client.sendMessage(user, message.getText());
    }
};

}

int
main(int argc, char *argv[])
{
    std::unique_ptr<bot::api::Request> request(new bot::api::Request(BOT_TOKEN));
    bot::Client client(request.get());

    client.registerObserver(new MessageLogger);
    client.registerObserver(new MessageReplyer);
    while (1) {
        client.processOnce();

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
