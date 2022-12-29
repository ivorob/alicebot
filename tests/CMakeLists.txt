CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
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
        ${SRC_DIR}/CurlRequest.cpp
        ${SRC_DIR}/types/User.cpp
        ${SRC_DIR}/types/Message.cpp
        ${SRC_DIR}/types/PhotoSize.cpp
        ${SRC_DIR}/types/File.cpp
        ${SRC_DIR}/types/Chat.cpp)

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} gtest jsoncpp_static)
TARGET_INCLUDE_DIRECTORIES (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

ADD_TEST (NAME ${PROJECT_NAME} COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
