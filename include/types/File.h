#ifndef __ALICE_BOT_FILE_H__
#define __ALICE_BOT_FILE_H__

#include <string>
#include <jsoncpp/json/json.h>

namespace bot {

class File {
public:
    File();
    File(const Json::Value& file);

    const std::string& getId() const;
    const std::string& getPath() const;

    size_t getSize() const;
private:
    std::string fileId;
    size_t size;
    std::string path;
};

}

#endif //__ALICE_BOT_FILE_H__
