#include <iostream>
#include "BotApiRequest.h"

#define BOT_TOKEN   "124206091:AAG-WjIsE6i4jC91qsQCmtcG69sli5mARh4"

int
main()
{
    bot::api::Request request(BOT_TOKEN);
    std::cout << request.perform("getUpdates") << std::endl;

    return 0;
}
