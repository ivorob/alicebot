#include "types/PhotoSize.h"

bot::PhotoSize::PhotoSize()
    : width(0),
      height(0),
      fileSize(0)
{
}

bot::PhotoSize::PhotoSize(const Json::Value& photoSize)
    : width(0),
      height(0),
      fileSize(0)
{
    if (photoSize.isObject()) {
        Json::Value fileId = photoSize.get("file_id", "");
        if (fileId.isString()) {
            this->fileId = fileId.asString();
        }

        Json::Value width = photoSize.get("width", 0);
        if (width.isNumeric()) {
            this->width = width.asInt();
        }

        Json::Value height = photoSize.get("height", 0);
        if (height.isNumeric()) {
            this->height = height.asInt();
        }

        Json::Value fileSize = photoSize.get("file_size", 0);
        if (fileSize.isNumeric()) {
            this->fileSize = fileSize.asInt();
        }
    }
}

const std::string&
bot::PhotoSize::getId() const
{
    return this->fileId;
}

int
bot::PhotoSize::getWidth() const
{
    return this->width;
}

int
bot::PhotoSize::getHeight() const
{
    return this->height;
}

int
bot::PhotoSize::getSize() const
{
    return this->fileSize;
}
