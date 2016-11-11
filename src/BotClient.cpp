#include <algorithm>
#include <sstream>
#include <iostream>
#include "BotClient.h"
#include "BotApiRequest.h"
#include "BotMessageObserver.h"
#include "types/File.h"

bot::Client::Client(bot::api::Request *request)
    : request(request),
      updateId(0)
{
    if (!this->request) {
        //TODO generate exception
    }
}

bool
bot::Client::hasObservers() const
{
    return this->observers.size() != 0;
}

void
bot::Client::registerObserver(MessageObserver *observer)
{
    if (observer != nullptr) {
        this->observers.push_back(observer);
    }
}

void
bot::Client::removeObserver(const std::string& name)
{
    observerContainer::iterator it = std::find_if(this->observers.begin(),
        this->observers.end(),
        [&](MessageObserver *currentItem) -> bool {
            if (currentItem->getName() == name) {
                return true;
            }

            return false;
        });
    if (it != this->observers.end()) {
        this->observers.erase(it);
        delete *it;
    }
}

void
bot::Client::processOnce()
{
    std::stringstream stream;
    stream << "offset=" << this->updateId;

    try {
        std::string response = this->request->perform("getUpdates",
                bot::api::RequestList({
                    bot::api::Request::value_type("offset", std::to_string(this->updateId))
                }));
        Json::Value root = parseResponse(response);
        processUpdates(root["result"]);
    } catch (const std::exception& e) { //TODO set particular exception
        std::cout << e.what() << std::endl;
    }
}

Json::Value
bot::Client::parseResponse(const std::string& response) const
{
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(response, root)) {
        //TODO generate exception
    }

    Json::Value status = root.get("ok", false);
    if (status.isBool() && !status.asBool()) {
        throw std::runtime_error("Some error in response: " + response);
    }

    return root;
}

void
bot::Client::processUpdates(const Json::Value& updates)
{
    if (updates.isArray() && updates.size() != 0) {
        for (Json::ArrayIndex i = 0;
             i != updates.size();
             ++i)
        {
            Json::Value id = updates[i].get("update_id", 0);
            if (id.isNumeric() && id.asInt() != 0) {
                this->updateId = id.asInt() + 1;

                this->lastMessage = updates[i].get("message", Json::Value());
                if (this->lastMessage.getId() != 0) {
                    fire();
                }
            }
        }
    }
}

void
bot::Client::fire()
{
    std::for_each(this->observers.begin(), this->observers.end(), 
        [this](MessageObserver *observer) {
            observer->handleMessage(*this);
        }
    );
}

void
bot::Client::startTask()
{
}

void
bot::Client::stopTask()
{
}

const bot::Message&
bot::Client::getLastMessage() const
{
    return this->lastMessage;
}

bot::User
bot::Client::getMe() const
{
    bot::User user;
    try {
        std::string response = this->request->perform("getMe");
        Json::Value result = parseResponse(response);

        user = bot::User(result.get("result", Json::Value()));
    } catch (const std::runtime_error& error) {
        //TODO: log error
    }

    return user;
}

bot::Chat
bot::Client::getChat() const
{
    bot::Chat chat;
    try {
        std::string response = this->request->perform("getChat");
        Json::Value result = parseResponse(response);

        chat = bot::Chat(result.get("result", Json::Value()));
    } catch (const std::runtime_error& error) {
        //TODO: log error
    }

    return chat;
}

void
bot::Client::sendMessage(const User& user, const std::string& text)
{
    this->request->perform("sendMessage",
            bot::api::RequestList({
                bot::api::Request::value_type("chat_id", std::to_string(user.getId())),
                bot::api::Request::value_type("text", text)
            }));
}

bot::File
bot::Client::getFile(const std::string& fileId)
{
    bot::File file;
    try {
        std::string response = this->request->perform("getFile",
                bot::api::RequestList({
                    bot::api::Request::value_type("file_id", fileId)
                }));
        Json::Value result = parseResponse(response);

        file = bot::File(result.get("result", Json::Value()));
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        //TODO: log error
    }

    return file;
}

std::string
bot::Client::downloadFile(const bot::File& file)
{
    return this->request->downloadFile(file.getPath());
}

std::string
bot::Client::sendPhoto(const bot::User& user, const std::string& path)
{
    return this->request->sendFile(user, path, "sendPhoto", "photo");
}
