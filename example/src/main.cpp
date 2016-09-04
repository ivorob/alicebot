#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <jsoncpp/json/json.h>
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
    //client.registerObserver(new ImageLogger);
    client.registerObserver(new MessageReplyer);
    while (1) {
        client.processOnce();

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
