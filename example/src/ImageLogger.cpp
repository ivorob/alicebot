#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include "BotClient.h"
#include "ImageLogger.h"
#include "types/Message.h"
#include "types/User.h"

ImageLogger::ImageLogger()
    : bot::MessageObserver("ImageLogger")
{
}

void
ImageLogger::handleMessage(bot::Client& client)
{
    const bot::Message& message = client.getLastMessage();
    const bot::User& user = message.getFrom();
    if (message.hasAttachments()) {
        //TODO photos
        //TODO getFile with max size
        //TODO download file
        //TODO save file
    }
};

std::string
ImageLogger::createOutputDirectory(int userId)
{
    std::string directory = ".";

    std::stringstream userDirectory;
    userDirectory << std::dec << userId;
    if (makeDirectory(userDirectory.str())) {
        userDirectory << "/image";
        if (makeDirectory(userDirectory.str())) {
            directory = userDirectory.str();
        }
    }

    return directory;
}

bool
ImageLogger::makeDirectory(const std::string& directory)
{
    int result = mkdir(directory.c_str(), 0777);
    return !result || (result == -1 && errno == EEXIST);
}

std::string
ImageLogger::makeFilename(const std::string& directory)
{
    std::time_t now = std::time(nullptr);
    char filename[128];
    std::strftime(filename, sizeof(filename), "%d.%m.%Y.log", std::localtime(&now));

    std::stringstream fullname;
    fullname << directory << "/" << filename;
    return fullname.str();
}
