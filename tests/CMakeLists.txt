CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ../src)
SET (SOURCES 
        AliceBotTestsSuite.cpp
        UserTest.cpp
        MessageTest.cpp
        BotApiRequestTest.cpp
        BotApiFakeRequest.cpp
        BotClientTest.cpp
        BotMessageObserverTest.cpp
        ${SRC_DIR}/User.cpp
        ${SRC_DIR}/Message.cpp
        ${SRC_DIR}/BotApiRequest.cpp
        ${SRC_DIR}/BotClient.cpp
        ${SRC_DIR}/BotMessageObserver.cpp)

ADD_DEFINITIONS (-std=c++0x)

EXECUTE_PROCESS (COMMAND curl-config --libs OUTPUT_VARIABLE CURL_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CURL_DEFINITIONS}")

INCLUDE_DIRECTORIES (../include)

FIND_LIBRARY (JSON_LIBRARY
    NAME jsoncpp
    PATHS /usr/lib /usr/local/lib)

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests cppunit ${JSON_LIBRARY})
