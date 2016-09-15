#ifndef __ALICE_BOT_CLIENT_H__
#define __ALICE_BOT_CLIENT_H__

#include <vector>
#include <string>
#include <json/json.h>
#include "types/Message.h"

namespace bot {

namespace api {

class Request;

}

class User;
class MessageObserver;
class File;

class Client {
public:
    Client() = delete;
    Client(bot::api::Request *request);

    bool hasObservers() const;

    void registerObserver(MessageObserver *observer);
    void removeObserver(const std::string& name);

    void processOnce();

    void startTask();
    void stopTask();

    const bot::Message& getLastMessage() const;

    // general methods
    User getMe() const;
    void sendMessage(const User& user, const std::string& text);
    File getFile(const std::string& fileId);
    std::string downloadFile(const File& file);
private:
    Json::Value parseResponse(const std::string& response) const;
    void processUpdates(const Json::Value& updates);
    void fire();
private:
    bot::api::Request *request;
    int updateId;
    typedef std::vector<MessageObserver *> observerContainer;
    observerContainer observers;
    bot::Message lastMessage;
};

}

#endif //__ALICE_BOT_CLIENT_H__
