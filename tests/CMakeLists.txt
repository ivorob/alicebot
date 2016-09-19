CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ../src)
SET (SOURCES 
        tests.cpp
        UserTest.cpp
        MessageTest.cpp
        BotApiRequestTest.cpp
        BotApiFakeRequest.cpp
        BotClientTest.cpp
        BotMessageObserverTest.cpp
        PhotoSizeTest.cpp
        FileTest.cpp
        ChatTest.cpp
        ${SRC_DIR}/BotApiRequest.cpp
        ${SRC_DIR}/BotClient.cpp
        ${SRC_DIR}/BotMessageObserver.cpp
        ${SRC_DIR}/types/User.cpp
        ${SRC_DIR}/types/Message.cpp
        ${SRC_DIR}/types/PhotoSize.cpp
        ${SRC_DIR}/types/File.cpp
        ${SRC_DIR}/types/Chat.cpp)

ADD_DEFINITIONS (-std=c++0x)

EXECUTE_PROCESS (COMMAND curl-config --libs OUTPUT_VARIABLE CURL_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CURL_DEFINITIONS}")

FIND_PATH (GTEST_INCLUDE_DIR
    NAME gtest/gtest.h
    PATHS /usr /usr/local
    PATH_PREFIX include)

FIND_PATH (JSONCPP_INCLUDE_DIR
    NAMES json/json.h
    PATH_SUFFIXES include include/jsoncpp)

INCLUDE_DIRECTORIES (../include ${GTEST_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR})

FIND_LIBRARY (GTEST_LIBRARY
    NAME gtest
    PATHS /usr/lib /usr/local/lib)

FIND_LIBRARY (JSON_LIBRARY
    NAME jsoncpp
    PATHS /usr/lib /usr/local/lib)

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests pthread ${JSON_LIBRARY} ${GTEST_LIBRARY})
