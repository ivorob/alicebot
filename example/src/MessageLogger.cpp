#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include "BotClient.h"
#include "MessageLogger.h"
#include "types/Message.h"
#include "types/User.h"

MessageLogger::MessageLogger()
    : bot::MessageObserver("Logger")
{
}

void
MessageLogger::handleMessage(bot::Client& client)
{
    const bot::Message& message = client.getLastMessage();
    const bot::User& user = message.getFrom();
    if (user.getId() != 0) {
        std::string directory = createOutputDirectory(user.getId());
        std::string filename = makeFilename(directory);
        std::ofstream output(filename, std::ios::out | std::ios::app);
        const std::string& text = message.getText();
        if (output.is_open() && !text.empty()) {
            output << "NEW MESSAGE:" << std::endl;
            output << "-------------------------" << std::endl;

            output << "From:" << std::endl
                   << "FIRST NAME: " << user.getFirstName() << std::endl <<
                      "LAST NAME : " << user.getLastName() << std::endl;

            time_t date = message.getDate();
            output << "date: " << std::ctime(&date)
                   << "text: " << std::endl
                   << text << std::endl << std::endl;
        }
    }
};

std::string
MessageLogger::createOutputDirectory(int userId)
{
    std::string directory = ".";

    std::stringstream userDirectory;
    userDirectory << std::dec << userId;
    if (makeDirectory(userDirectory.str())) {
        userDirectory << "/text";
        if (makeDirectory(userDirectory.str())) {
            directory = userDirectory.str();
        }
    }

    return directory;
}

bool
MessageLogger::makeDirectory(const std::string& directory)
{
    int result = mkdir(directory.c_str(), 0777);
    return !result || (result == -1 && errno == EEXIST);
}

std::string
MessageLogger::makeFilename(const std::string& directory)
{
    std::time_t now = std::time(nullptr);
    char filename[128];
    std::strftime(filename, sizeof(filename), "%d.%m.%Y.log", std::localtime(&now));

    std::stringstream fullname;
    fullname << directory << "/" << filename;
    return fullname.str();
}
