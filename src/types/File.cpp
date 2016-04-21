#include "types/File.h"

bot::File::File()
    : size(0)
{
}

bot::File::File(const Json::Value& file)
    : size(0)
{
    if (file.isObject()) {
        Json::Value fileId = file.get("file_id", "");
        if (fileId.isString()) {
            this->fileId = fileId.asString();
        }

        Json::Value fileSize = file.get("file_size", 0);
        if (fileSize.isNumeric()) {
            this->size = fileSize.asInt();
        }

        Json::Value filePath = file.get("file_path", "");
        if (filePath.isString()) {
            this->path = filePath.asString();
        }
    }
}

const std::string&
bot::File::getId() const
{
    return this->fileId;
}

size_t
bot::File::getSize() const
{
    return this->size;
}

const std::string&
bot::File::getPath() const
{
    return this->path;
}
