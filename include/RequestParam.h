#ifndef __ALICE_BOT_REQUEST_PARAM_H__
#define __ALICE_BOT_REQUEST_PARAM_H__

#include <string>

namespace HttpRequest {

class BaseParam {
public:
    typedef std::pair<std::string,std::string> value_type;
public:
    virtual value_type const& getData() const {
        return this->pair;
    }
protected:
    value_type pair;
};

template <typename T>
class Param : public BaseParam {
public:
    Param(const std::string& key, T const& value) {
        this->pair.first = key;
        this->pair.second = std::to_string(value);
    }
};

template <>
class Param<char *> : public BaseParam {
public:
    Param(const std::string& key, const std::string& value) {
        this->pair.first = key;
        this->pair.second = value;
    }
};

template <>
class Param<std::string> : public BaseParam {
public:
    Param(const std::string& key, const std::string& value) {
        this->pair.first = key;
        this->pair.second = value;
    }
};

}

#endif //__ALICE_BOT_REQUEST_PARAM_H__
