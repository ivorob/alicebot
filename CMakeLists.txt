CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (alicebot)

OPTION (BUILD_TESTING OFF)

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
        ${SRC_DIR}/types/Chat.cpp
    )

SET (CMAKE_CXX_STANDARD 17)

EXECUTE_PROCESS (COMMAND curl-config --libs OUTPUT_VARIABLE CURL_DEFINITIONS OUTPUT_STRIP_TRAILING_WHITESPACE)
SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CURL_DEFINITIONS}")

SET (CMAKE_MACOSX_RPATH 1)

ADD_SUBDIRECTORY (thirdparty)

# add example to compile
ADD_SUBDIRECTORY (example)

ADD_LIBRARY(alicebot SHARED ${SOURCES})
TARGET_INCLUDE_DIRECTORIES (alicebot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES (alicebot PRIVATE jsoncpp_static)
TARGET_LINK_LIBRARIES (alicebot PRIVATE libcurl)

IF (BUILD_TESTING)
    ENABLE_TESTING ()
    ADD_SUBDIRECTORY (tests)
ENDIF ()
