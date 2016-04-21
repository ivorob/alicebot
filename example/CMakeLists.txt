CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (alice-telegram-bot)

SET (SRC_DIR src)
SET (BOTAPI_SRC_DIR ../src)
SET (SOURCES 
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/MessageLogger.cpp
        ${SRC_DIR}/ImageLogger.cpp)

ADD_DEFINITIONS (-std=gnu++0x)

INCLUDE_DIRECTORIES (../include/)

# compile library first
FIND_LIBRARY (BOTAPI_LIBRARY
    NAME alicebot
    PATHS ../)

ADD_EXECUTABLE (alice-telegram-bot ${SOURCES})
TARGET_LINK_LIBRARIES (alice-telegram-bot ${BOTAPI_LIBRARY})
