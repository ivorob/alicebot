#ifndef __ALICE_BOT_MESSAGE_OBSERVER_H__
#define __ALICE_BOT_MESSAGE_OBSERVER_H__

#include <string>

namespace bot {

class Client;

class MessageObserver {
public:
    MessageObserver() = default;
    MessageObserver(const std::string& name);
    virtual ~MessageObserver();

    const std::string& getName() const;

    virtual void handleMessage(bot::Client& client) = 0;
private:
    std::string name;
};

}

#endif //__ALICE_BOT_MESSAGE_OBSERVER_H__
