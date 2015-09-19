#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <jsoncpp/json/json.h>
#include "BotApiRequest.h"
#include "User.h"
#include "Message.h"

#define BOT_TOKEN   "124206091:AAG-WjIsE6i4jC91qsQCmtcG69sli5mARh4"

void
ShowUser(const bot::User& user)
{
    std::cout << "USER ID   : " << user.getId() << std::endl;
    std::cout << "FIRST NAME: " << user.getFirstName() << std::endl;
    std::cout << "LAST NAME : " << user.getLastName() << std::endl;
}

int
ProcessMessageAndGetLastUpdateId(bot::api::Request& request, const std::string& response)
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(response, root)) {
        return 0;
    }

    Json::Value status = root.get("ok", false);
    if (status.isBool() && !status.asBool()) {
        return 0;
    }

    int updateId = 0;
    Json::Value updates = root["result"];
    if (updates.isArray() && updates.size() != 0) {
        std::cout << std::endl << "RESPONSE: " << std::endl;
        std::cout << response << std::endl;

        for (Json::ArrayIndex i = 0;
             i != updates.size();
            ++i)
        {
            Json::Value id = updates[i].get("update_id", 0);
            if (id.isNumeric() && id.asInt() != 0) {
                updateId = id.asInt();

                bot::Message message = updates[i].get("message", Json::Value());
                if (message.getId() != 0) {
                    std::cout << "Message: " << message.getId() << std::endl;
                    std::cout << "Message from: " << std::endl;
                    ShowUser(message.getFrom());
                    std::cout << "Message text: " << std::endl;
                    std::cout << message.getText() << std::endl;
                    std::cout << std::endl;
                }

                const bot::User& user = message.getFrom();
                std::stringstream stream;
                std::string text = request.urlencode(message.getText());
                stream << "chat_id=" << user.getId() << "&text=" << text;

                request.perform("sendMessage", stream.str());
            }
        }
    }

    return updateId;
}

int
main(int argc, char *argv[])
{
    bot::api::Request request(BOT_TOKEN);
    std::string response = request.perform("getUpdates");

    int lastUpdateId = 0;
    while (1) {
        int updateId = ProcessMessageAndGetLastUpdateId(request, response);
        if (updateId != 0) {
            lastUpdateId = updateId + 1;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::stringstream stream;
        stream << "offset=" << lastUpdateId;
        response = request.perform("getUpdates", stream.str());
    }

    return 0;
}
