CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (alicebot)

SET (SRC_DIR src)
SET (SOURCES 
        ${SRC_DIR}/BotApiRequest.cpp
        ${SRC_DIR}/BotMessageObserver.cpp
        ${SRC_DIR}/BotClient.cpp
        # types
        ${SRC_DIR}/types/Message.cpp
        ${SRC_DIR}/types/User.cpp)

ADD_DEFINITIONS (-std=gnu++0x)

EXECUTE_PROCESS (COMMAND curl-config --libs OUTPUT_VARIABLE CURL_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CURL_DEFINITIONS}")

INCLUDE_DIRECTORIES (include/)

# add example to compile
ADD_SUBDIRECTORY (example)

FIND_LIBRARY (JSON_LIBRARY
    NAME jsoncpp
    PATHS /usr/lib /usr/local/lib)

ADD_LIBRARY(alicebot SHARED ${SOURCES})
TARGET_LINK_LIBRARIES (alicebot ${JSON_LIBRARY})
