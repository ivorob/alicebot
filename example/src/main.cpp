#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <json/json.h>
#include "BotApiRequest.h"
#include "BotMessageObserver.h"
#include "MessageLogger.h"
#include "ImageLogger.h"
#include "BotClient.h"
#include "types/User.h"
#include "types/Message.h"

#define BOT_TOKEN   "124206091:AAG-WjIsE6i4jC91qsQCmtcG69sli5mARh4"

namespace {

class MessageReplyer: public bot::MessageObserver {
public:
    MessageReplyer()
        : bot::MessageObserver("Replyer")
    {
    }

    virtual void handleMessage(bot::Client& client) {
        const bot::Message& message = client.getLastMessage();
        const bot::User& user = message.getFrom();
        const std::string& text = message.getText();
        if (!text.empty()) {
            client.sendMessage(user, message.getText());
        }
    }
};

}

int
main(int argc, char *argv[])
{
    std::unique_ptr<bot::api::Request> request(new bot::api::Request(BOT_TOKEN));
    bot::Client client(request.get());

    bot::User bot = client.getMe();
    std::cout << "Starting bot: @" << bot.getLogin() << " ["
        << bot.getFirstName() << " " << bot.getLastName() << "]...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\tOK" << std::endl;

    client.registerObserver(new MessageLogger);
    client.registerObserver(new ImageLogger);
    client.registerObserver(new MessageReplyer);
    while (1) {
        client.processOnce();

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
