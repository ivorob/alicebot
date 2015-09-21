#include "types/Message.h"

bot::Message::Message()
    : messageId(0)
{
}

bot::Message::Message(const Json::Value& message)
    : messageId(0)
{
    if (message.isObject()) {
        Json::Value messageId = message.get("message_id", 0);
        if (messageId.isNumeric()) {
            this->messageId = messageId.asInt();
        }

        Json::Value from = message.get("from", Json::Value());
        if (from.isObject()) {
            this->from = from;
        }

        Json::Value text = message.get("text", "");
        if (text.isString()) {
            this->text = text.asString();
        }

        Json::Value date = message.get("date", 0);
        if (date.isNumeric()) {
            this->date = date.asInt();
        }
    }
}

int
bot::Message::getId() const
{
    return this->messageId;
}

bot::User
bot::Message::getFrom() const
{
    return this->from;
}

const std::string&
bot::Message::getText() const
{
    return this->text;
}

const time_t&
bot::Message::getDate() const
{
    return this->date;
}
