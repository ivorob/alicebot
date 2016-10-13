CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (alicebot)

SET (SRC_DIR src)
SET (SOURCES 
        ${SRC_DIR}/BotApiRequest.cpp
        ${SRC_DIR}/BotMessageObserver.cpp
        ${SRC_DIR}/BotClient.cpp
        ${SRC_DIR}/CurlRequest.cpp
        # types
        ${SRC_DIR}/types/Message.cpp
        ${SRC_DIR}/types/User.cpp
        ${SRC_DIR}/types/File.cpp
        ${SRC_DIR}/types/PhotoSize.cpp
        ${SRC_DIR}/types/Chat.cpp)

ADD_DEFINITIONS (-std=gnu++0x)

EXECUTE_PROCESS (COMMAND curl-config --libs OUTPUT_VARIABLE CURL_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CURL_DEFINITIONS}")

SET (CMAKE_MACOSX_RPATH 1)

# add example to compile
#ADD_SUBDIRECTORY (example)

FIND_LIBRARY (JSON_LIBRARY
    NAME jsoncpp
    PATHS /usr/lib /usr/local/lib)

FIND_PATH (JSONCPP_INCLUDE_DIR
    NAMES json/json.h
    PATH_SUFFIXES include include/jsoncpp)

INCLUDE_DIRECTORIES (include/ ${JSONCPP_INCLUDE_DIR})

SET (CMAKE_FIND_LIBRARY_SUFFIX ".a")
FIND_LIBRARY (CURL_LIBRARY
    NAME curl
    PATHS /usr/lib /usr/local/lib)

ADD_LIBRARY(alicebot SHARED ${SOURCES})
TARGET_LINK_LIBRARIES (alicebot ${JSON_LIBRARY} ${CURL_LIBRARY})
