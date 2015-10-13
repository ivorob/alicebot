#ifndef __ALICE_MESSAGE_LOGGER_H__
#define __ALICE_MESSAGE_LOGGER_H__

#include "BotMessageObserver.h"

class MessageLogger: public bot::MessageObserver {
public:
    MessageLogger();

    virtual void handleMessage(bot::Client& client);
private:
    std::string createOutputDirectory(int userId);
    std::string makeFilename(const std::string& directory);

    bool makeDirectory(const std::string& directory);
};

#endif //__ALICE_MESSAGE_LOGGER_H__
