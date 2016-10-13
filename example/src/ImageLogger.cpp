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
#include "types/File.h"

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
        bot::PhotoSize highQualityPhoto;

        const bot::Message::Photo& photo = message.getPhoto();

        int maxSize = 0;
        for (const bot::PhotoSize& currentPhoto : photo) {
            if (currentPhoto.getSize() > maxSize) {
                highQualityPhoto = currentPhoto;
            }
        }

        const bot::File file = client.getFile(highQualityPhoto.getId());
        if (!file.getPath().empty()) {
            std::string fileContent = client.downloadFile(file);
            if (!fileContent.empty()) {
                std::string directory = createOutputDirectory(user.getId());
                std::string filename = makeFilename(directory);
                std::ofstream output(filename, std::ios::out | std::ios::binary);
                if (output.is_open()) {
                    output.write(fileContent.c_str(), fileContent.size());
                    output.close();

                    client.sendPhoto(user, filename);
                }
            }
        }
    }
};

std::string
ImageLogger::createOutputDirectory(int userId)
{
    std::string directory = ".";

    std::stringstream userDirectory;
    userDirectory << std::dec << userId;
    if (makeDirectory(userDirectory.str())) {
        userDirectory << "/images";
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
    std::strftime(filename, sizeof(filename), "%d.%m.%Y.%H%M%S.jpg", std::localtime(&now));

    std::stringstream fullname;
    fullname << directory << "/" << filename;
    return fullname.str();
}
