#ifndef __ALICE_BOT_PHOTO_SIZE_H__
#define __ALICE_BOT_PHOTO_SIZE_H__

#include <string>
#include <jsoncpp/json/json.h>

namespace bot {

class PhotoSize {
public:
    PhotoSize();
    PhotoSize(const Json::Value& photoSize);

    const std::string& getId() const;
    int getWidth() const;
    int getHeight() const;
    int getSize() const;
private:
    std::string fileId;
    int width, height;
    int fileSize;
};

}

#endif //__ALICE_BOT_PHOTO_SIZE_H__
