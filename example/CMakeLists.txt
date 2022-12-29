CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (alice-telegram-bot)

SET (SRC_DIR src)
SET (BOTAPI_SRC_DIR ../src)
SET (SOURCES 
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/MessageLogger.cpp
        ${SRC_DIR}/ImageLogger.cpp)

ADD_EXECUTABLE (${PROJECT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES (${PROJECT_NAME} alicebot)
TARGET_LINK_LIBRARIES (${PROJECT_NAME} jsoncpp_static)
