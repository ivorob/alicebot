#include "BotMessageObserver.h"

bot::MessageObserver::MessageObserver(const std::string& name)
    : name(name)
{
}

bot::MessageObserver::~MessageObserver()
{
}

const std::string&
bot::MessageObserver::getName() const
{
    return this->name;
}
